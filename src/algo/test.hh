#ifndef PREGEL_TEST_VERTEX
#define PREGEL_TEST_VERTEX

#include "../pregel.hh"

// test node
class Test : public Vertex<int, Edge<Test*, int>, int> {
    public:
        Test(std::string v_id, int v_value, std::vector<Edge<Test*, int>*> v_edges);
        ~Test();
        void Compute() override;
};

std::vector<Test*> generate_seven_test_nodes();

#endif
