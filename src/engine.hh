#ifndef PREGEL_ENGINE
#define PREGEL_ENGINE

#include <condition_variable>
#include <semaphore>
#include <stdexcept>
#include <thread>
#include <vector>
#include <unordered_map>
#include <utility>

template <typename V>
void pregel_worker(
    std::vector<V*> nodes, 
    std::condition_variable& cv_v, 
    std::mutex& cv_m,
    std::pair<std::binary_semaphore*, bool>* s,
    bool& join_now
) {
    std::unique_lock<std::mutex> lk(cv_m);

    while (!join_now) {
        cv_v.wait(lk);
        if (join_now) break;

        s->second = false;
        for (auto v : nodes) {
            if (v->is_active() || v->get_incoming_msg().size() > 0) {
                v->Compute();
            }
            s->second |= v->is_active();
        }
        s->first->release();
    }
}

template <typename V>
class PregelEngine {
    public:
        PregelEngine(std::vector<V*> v_verticies, int num_workers);
        ~PregelEngine();
        void run();
    private:
        void distribute_messages();

        std::vector<V*> verticies;
        std::unordered_map<std::string, V*> vertex_map;
        
        bool join_now;
        std::condition_variable cv_v;
        std::mutex cv_m;

        std::vector<std::thread> workers;
        std::vector<std::pair<std::binary_semaphore*, bool>*> statuses;
};

template <typename V>
PregelEngine<V>::PregelEngine(std::vector<V*> v_verticies, int num_workers) {
    verticies = v_verticies;
    join_now = false;
    if (num_workers <= 0) {
        throw std::invalid_argument("Number of workers should be positive");
    }

    // create partitions setup
    std::vector<std::vector<V*> > partitions;
    std::hash<std::string> hasher;
    for (int i = 0; i < num_workers; i++) {
        partitions.push_back(std::vector<V*>());
    }

    // add to partitions + add to hashmap
    for (auto v : verticies) {
        vertex_map[v->vertex_id()] = v;
        std::size_t h = hasher(v->vertex_id());
        int i = static_cast<int>(h) % num_workers;
        // for some reason hashing goes neg.
        if (i < 0) i += num_workers;
        partitions.at(i).push_back(v);
    }

    // start threads (add to vector), initialize semaphore pair
    for (auto pt : partitions) {
        if (pt.size() == 0) continue;
        auto s = new std::binary_semaphore(0);
        auto p = new std::pair<std::binary_semaphore *, bool>(s, true);
        statuses.push_back(p);
        workers.push_back(std::thread(pregel_worker<V>, pt, std::ref(cv_v), std::ref(cv_m), p, std::ref(join_now)));
    }
}

template <typename V>
PregelEngine<V>::~PregelEngine() {
    for (int i = 0; i < workers.size(); i++) {
        workers.at(i).join();
    }

    for (auto p : statuses) {
        delete p->first;
        delete p;
    }

    for (auto v : verticies) {
        delete v;
    }
}

template <typename V>
void PregelEngine<V>::run() {
    bool cont;
    do {
        cont = false;
        { std::lock_guard<std::mutex> lk(cv_m); }
        cv_v.notify_all();
        for (auto p : statuses) {
            p->first->acquire();
            cont |= p->second;
        }
        distribute_messages();
    } while(cont);

    join_now = true;
    { std::lock_guard<std::mutex> lk(cv_m); }
    cv_v.notify_all();
}

template <typename V>
void PregelEngine<V>::distribute_messages() {
    for (auto v : verticies) {
        v->clear_incoming_msg();
    }
    for (auto v : verticies) {
        for (auto m : v->get_outgoing_msg()) {
            vertex_map[m.first]->add_to_incoming(m.second);
        }
        v->clear_outgoing_msg();
        v->increment_superstep();
    }
}

#endif
