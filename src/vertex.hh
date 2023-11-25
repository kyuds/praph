#ifndef PREGEL_VERTEX
#define PREGEL_VERTEX

#include <iostream>
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

// IMPL
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
    std::cout << "SUPER DESTRUCTOR" << std::endl;
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

}

#endif