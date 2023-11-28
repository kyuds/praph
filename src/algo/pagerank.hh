#ifndef PREGEL_PAGERANK
#define PREGEL_PAGERANK

#include "../pregel.hh"

#include <vector>

class PageRankVertex : public Vertex<double, Edge<PageRankVertex, int>, double> {
    public:
        PageRankVertex(std::string v_id, double v_value, std::vector<Edge<PageRankVertex, int>*> v_edges, int p_num_vertex);
        ~PageRankVertex();
        void addOutEdge(PageRankVertex * p);
        void Compute() override;
    private:
        int num_vertex;
};

std::vector<PageRankVertex*> generate_graph();

#endif
