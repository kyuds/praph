#ifndef PREGEL_TEST_VERTEX
#define PREGEL_TEST_VERTEX

#include "../vertex.hh"

class Test : Vertex<int, int, int> {
    public:
        Test(std::string& v_id, int v_value, std::vector<int*> v_edges);
        ~Test();
        void Compute(std::vector<int*> msgs) override;
};

#endif