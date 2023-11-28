#ifndef PREGEL_TEMPLATE
#define PREGEL_TEMPLATE

#include <string>
#include <utility>
#include <vector>

// refer <Fig 3> in the Pregel paper
template <typename VV, typename EV, typename MV>
class Vertex {
    public:
        Vertex(std::string v_id, VV v_value, std::vector<EV*> v_edges);
        virtual ~Vertex();
        virtual void Compute() {};

        const std::string& vertex_id() const;
        unsigned int get_superstep() const;
        void increment_superstep();

        const VV& get_value() const;
        VV* mutable_value();
        std::vector<EV*>& get_edges();

        void send_msg(const std::string& id, MV msg);
        void vote_halt();
        bool is_active();
        void set_active();

        std::vector<std::pair<std::string, MV> >& get_outgoing_msg();
        std::vector<MV>& get_incoming_msg();
        void clear_incoming_msg();
        void clear_outgoing_msg();
        void add_to_incoming(MV msg);
    private:
        std::string id;
        unsigned int superstep;
        bool active;

        VV value;
        std::vector<EV*> edges;

        std::vector<std::pair<std::string, MV> > o_msg;
        std::vector<MV> i_msg;
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
void Vertex<VV, EV, MV>::send_msg(const std::string& id, MV msg) {
    o_msg.push_back(std::make_pair(id, msg));
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

template <typename VV, typename EV, typename MV>
std::vector<std::pair<std::string, MV> >& Vertex<VV, EV, MV>::get_outgoing_msg() {
    return o_msg;
}

template <typename VV, typename EV, typename MV>
std::vector<MV>& Vertex<VV, EV, MV>::get_incoming_msg() {
    return i_msg;
}

template <typename VV, typename EV, typename MV>
void Vertex<VV, EV, MV>::clear_incoming_msg() {
    i_msg.clear();
}

template <typename VV, typename EV, typename MV>
void Vertex<VV, EV, MV>::clear_outgoing_msg() {
    o_msg.clear();
}

template <typename VV, typename EV, typename MV>
void Vertex<VV, EV, MV>::add_to_incoming(MV msg) {
    i_msg.push_back(msg);
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
