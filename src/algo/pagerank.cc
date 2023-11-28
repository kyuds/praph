#include "pagerank.hh"

PageRankVertex::PageRankVertex(std::string v_id, double v_value, std::vector<Edge<PageRankVertex, int>*> v_edges, int p_num_vertex) 
    :  Vertex<double, Edge<PageRankVertex, int>, double>(v_id, v_value, v_edges)
{
    num_vertex = p_num_vertex;
}

PageRankVertex::~PageRankVertex() {}

void PageRankVertex::Compute() {
    if (get_superstep() >= 1) {
        double sum = 0;
        for (auto m : get_incoming_msg()) {
            sum += m;
        }
        double * mv = mutable_value();
        *mv = sum * 0.85 + num_vertex * 0.15;
    }
    if (get_superstep() < 30) {
        int n = get_edges().size();
        double msg_value = get_value() / n;
        for (auto e : get_edges()) {
            send_msg(e->get_dest()->vertex_id(), msg_value);
        }
    } else {
        vote_halt();
    }
}

void PageRankVertex::addOutEdge(PageRankVertex * p) {
    get_edges().push_back(new Edge<PageRankVertex, int>(p, 0));
}

std::vector<PageRankVertex*> generate_graph() {

}
