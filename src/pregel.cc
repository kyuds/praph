#include "pregel.hh"

#include <iostream>
#include <unordered_map>

// Pregel Engine Member Functions

// Instantiate verticies, number of workers, and thread pool.
template <typename VV, typename EV, typename MV>
PregelEngine<VV, EV, MV>::PregelEngine(std::vector<Vertex<VV, EV, MV>*>& vertices, int n) {
    // member variables
    num_workers = n;
    join_now = false;

    // initialize partitions based on simple hashing.
    partitions = std::vector<std::vector<Vertex<VV, EV, MV>*> >();
    for (int i = 0; i < n; ++i) {
        partitions.push_back(std::vector<Vertex<VV, EV, MV>*>());
    }
    std::hash<std::string> hasher;
    for (auto v : vertices) {
        std::size_t h = hasher(v->vertex_id());
        int i = static_cast<int>(h) % n;
        partitions.at(i).push_back(v);
    }

    // testing purposes
    for (auto p : partitions) {
        for (auto v : p) {
            std::cout << v->vertex_id() << " ";
        }
        std::cout << std::endl;
    }

    // initialize threads.
}

template <typename VV, typename EV, typename MV>
PregelEngine<VV, EV, MV>::~PregelEngine() {

}

template <typename VV, typename EV, typename MV>
void PregelEngine<VV, EV, MV>::run() {

}

// Helper methods. 
template <typename VV, typename EV, typename MV>
void PregelEngine<VV, EV, MV>::superstep() {

}

template <typename VV, typename EV, typename MV>
bool PregelEngine<VV, EV, MV>::is_active() {
    return true;
}

template <typename VV, typename EV, typename MV>
void PregelEngine<VV, EV, MV>::distribute_messages() {

}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

// Vertex Member Functions
template <typename VV, typename EV, typename MV>
Vertex<VV, EV, MV>::Vertex(std::string& v_id, VV& v_value, std::vector<EV*>& v_edges) {
    id = v_id;
    value = v_value;
    edges = v_edges;

    superstep = 0;
    active = true;
}

template <typename VV, typename EV, typename MV>
const std::string& Vertex<VV, EV, MV>::vertex_id() const {

}

template <typename VV, typename EV, typename MV>
unsigned int Vertex<VV, EV, MV>::get_superstep() const {

}

template <typename VV, typename EV, typename MV>
const VV& Vertex<VV, EV, MV>::get_value() const {

}

template <typename VV, typename EV, typename MV>
VV* Vertex<VV, EV, MV>::mutable_value() {

}

template <typename VV, typename EV, typename MV>
std::vector<EV*>& Vertex<VV, EV, MV>::get_edges() {

}

template <typename VV, typename EV, typename MV>
void Vertex<VV, EV, MV>::send_msg(const std::string& id, MV* msg) {

}

template <typename VV, typename EV, typename MV>
void Vertex<VV, EV, MV>::vote_halt() {

}