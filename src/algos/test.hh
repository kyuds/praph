#ifndef PREGEL_TEST_VERTEX
#define PREGEL_TEST_VERTEX

#include "../pregel.hh"

class Test : public Vertex<int, Edge<Test*, int>, int> {
    public:
        Test(std::string v_id, int v_value, std::vector<Edge<Test*, int>*> v_edges);
        ~Test();
        void Compute(std::vector<int*> msgs) override;
};

std::vector<Test*> generate_five_test_nodes();

#endif