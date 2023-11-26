#ifndef PREGEL_TEMPLATE
#define PREGEL_TEMPLATE

#include <string>
#include <vector>

// refer <Fig 3> in the Pregel paper
template <typename VV, typename EV, typename MV>
class Vertex {
    public:
        Vertex(std::string v_id, VV v_value, std::vector<EV*> v_edges);
        virtual ~Vertex();
        virtual void Compute(std::vector<MV*> msgs) {};

        const std::string& vertex_id() const;
        unsigned int get_superstep() const;
        void increment_superstep();

        const VV& get_value() const;
        VV* mutable_value();
        std::vector<EV*>& get_edges();

        void send_msg(const std::string& id, MV* msg);
        void vote_halt();
        bool is_active();
        void set_active();
    private:
        std::string id;
        unsigned int superstep;
        bool active;

        VV value;
        std::vector<EV*> edges;
};

// Generic Vertex implementation
template <typename VV, typename EV, typename MV>
Vertex<VV, EV, MV>::Vertex(std::string v_id, VV v_value, std::vector<EV*> v_edges) {
    id = v_id;
    value = v_value;
    edges = v_edges;

    superstep = 0;
    active = true;
}

template<typename VV, typename EV, typename MV>
Vertex<VV, EV, MV>::~Vertex() {
    for (auto ev : edges) {
        delete ev;
    }
    // need to free message iterator too?
}

template <typename VV, typename EV, typename MV>
const std::string& Vertex<VV, EV, MV>::vertex_id() const {
    return id;
}

template <typename VV, typename EV, typename MV>
unsigned int Vertex<VV, EV, MV>::get_superstep() const {
    return superstep;
}

template <typename VV, typename EV, typename MV>
void Vertex<VV, EV, MV>::increment_superstep() {
    superstep++;
}

template <typename VV, typename EV, typename MV>
const VV& Vertex<VV, EV, MV>::get_value() const {
    return value;
}

template <typename VV, typename EV, typename MV>
VV* Vertex<VV, EV, MV>::mutable_value() {
    return &value;
}

template <typename VV, typename EV, typename MV>
std::vector<EV*>& Vertex<VV, EV, MV>::get_edges() {
    return edges;
}

template <typename VV, typename EV, typename MV>
void Vertex<VV, EV, MV>::send_msg(const std::string& id, MV* msg) {

}

template <typename VV, typename EV, typename MV>
void Vertex<VV, EV, MV>::vote_halt() {
    active = false;
}

template <typename VV, typename EV, typename MV>
bool Vertex<VV, EV, MV>::is_active() {
    return active;
}

template <typename VV, typename EV, typename MV>
void Vertex<VV, EV, MV>::set_active() {
    active = true;
}

// edge template class
template <typename VV, typename EV>
class Edge {
    public:
        Edge(VV* v_dest, EV v_value) {
            dest = v_dest;
            value = v_value;
        }
        virtual ~Edge() {};

        VV* get_dest() { return dest; }
        EV get_value() { return value; }

        void change_dest(VV* new_dest) { dest = new_dest; }
        void change_value(EV new_value) { value = new_value; }

    private:
        VV* dest;
        EV value;
};

#endif
