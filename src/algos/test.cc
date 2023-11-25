#include "test.hh"

#include <iostream>

Test::Test(std::string& v_id, int v_value, std::vector<int*> v_edges) 
    : Vertex<int, int, int>(v_id, v_value, v_edges)
{
    std::cout << "TEST!" << std::endl;
}

Test::~Test() {
    std::cout << "IMPL DESTRUCTOR!" << std::endl;
}

void Test::Compute(std::vector<int*> msgs) {
    std::cout << "hi" << std::endl;
}

