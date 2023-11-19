#ifndef PREGEL_ENGINE
#define PREGEL_ENGINE

#include <string>
#include <vector>

// refer <Fig 3> in the Pregel paper
template <typename VV, typename EV, typename MV>
class Vertex {
    public:
        Vertex(std::string& v_id, VV& v_value, std::vector<EV*>& v_edges);
        virtual void Compute(std::vector<MV*> msgs) {};

        const std::string& vertex_id() const;
        unsigned int get_superstep() const;

        const VV& get_value() const;
        VV* mutable_value();
        std::vector<EV*>& get_edges();

        void send_msg(const std::string& id, MV* msg);
        void vote_halt();
    private:
        std::string id;
        unsigned int superstep;
        bool active;

        VV value;
        std::vector<EV*> edges;
};

// multithreaded engine to simulate Pregel
template <typename VV, typename EV, typename MV>
class PregelEngine {
    public:
        PregelEngine(std::vector<Vertex<VV, EV, MV>*>& v, int n);
        ~PregelEngine();
        void run();
    private:
        std::vector<std::vector<Vertex<VV, EV, MV>*> > partitions;
        int num_workers;
        bool join_now;

        void superstep();
        bool is_active();
        void distribute_messages();
};

#endif