#ifndef PREGEL_SIMULATOR
#define PREGEL_SIMULATOR

#include <semaphore>
#include <vector>
#include <thread>
#include <unordered_map>
#include <utility>

template <typename V>
class PregelWorker {
    public:
        PregelWorker(std::vector<V*> _nodes) { nodes = _nodes; }
        ~PregelWorker() {}

        bool halted() { return stopped; }
        void setHalt(bool b) { stopped = b; }
        std::vector<V*>& getNodes() { return nodes; }

        std::counting_semaphore<1>& waker() { return wakeWorker; }
        std::counting_semaphore<1>& signal() { return signalDone; }
    
    private:
        bool stopped;
        std::vector<V*> nodes;

        std::counting_semaphore<1> wakeWorker {0};
        std::counting_semaphore<1> signalDone {0};
};

template <typename V>
void thread_func(PregelWorker<V> * worker, bool& joinNow) {
    while (!joinNow) {
        worker->waker().acquire();
        if (joinNow) break;

        // do work on all nodes.
        bool halt = false;
        for (auto v : worker->getNodes()) {
            if (v->is_active() || v->get_incoming_msg().size() > 0) {
                v->Compute();
            }
            halt |= v->is_active();
        }
        worker->setHalt(halt);

        worker->signal().release();
    }
}

template <typename V>
class PregelEngine {
    public:
        PregelEngine(std::vector<V*> _verticies, int num_workers);
        ~PregelEngine();
        void run();
    private:
        void distribute_messages();

        std::vector<V*> verticies;
        std::unordered_map<std::string, V*> vertex_map;
        
        bool join_now;

        std::vector<std::thread> threads;
        std::vector<PregelWorker<V>*> workers;
};

template <typename V>
PregelEngine<V>::PregelEngine(std::vector<V*> _verticies, int num_workers) {
    verticies = _verticies;
    join_now = false;

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
        PregelWorker<V> * w = new PregelWorker<V>(pt);
        threads.push_back(std::thread(thread_func<V>, w, std::ref(join_now)));
        workers.push_back(w);
    }
}

template <typename V>
PregelEngine<V>::~PregelEngine() {
    for (int i = 0; i < threads.size(); i++) {
        threads.at(i).join();
    }
    for (auto v : verticies) {
        delete v;
    }
    for (auto w : workers) {
        delete w; 
    }
}

template <typename V>
void PregelEngine<V>::run() {
    bool cont;
    do {
        cont = false;
        for (auto w : workers) {
            w->waker().release();
        }
        for (auto w : workers) {
            w->signal().acquire();
            cont |= w->halted();
        }

        distribute_messages();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    } while(cont);

    join_now = true;
    for (auto w : workers) {
        w->waker().release();
    }
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
