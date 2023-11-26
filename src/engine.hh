#ifndef PREGEL_ENGINE
#define PREGEL_ENGINE

#include <chrono>
#include <condition_variable>
#include <semaphore>
#include <stdexcept>
#include <thread>
#include <vector>
#include <unordered_map>
#include <utility>

#include <iostream>

template <typename V>
void pregel_worker(
    std::vector<V*>& nodes, 
    std::condition_variable& cv_v, 
    std::mutex& cv_m,
    std::pair<std::binary_semaphore*, bool>* s,
    bool& join_now
) {
    std::unique_lock<std::mutex> lk(cv_m);

    cv_v.wait(lk);
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
        workers.push_back(std::thread(pregel_worker<V>, std::ref(pt), std::ref(cv_v), std::ref(cv_m), p, std::ref(join_now)));
    }
}

template <typename V>
PregelEngine<V>::~PregelEngine() {
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
    for (int i = 0; i < workers.size(); i++) {
        workers.at(i).join();
    }
}

template <typename V>
void PregelEngine<V>::distribute_messages() {

}

#endif