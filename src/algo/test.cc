#include "test.hh"

#include <chrono>
#include <iostream>
#include <thread>

Test::Test(std::string v_id, int v_value, std::vector<Edge<Test*, int>*> v_edges) 
    : Vertex<int, Edge<Test*, int>, int>(v_id, v_value, v_edges)
{
    //std::cout << "TEST!" << std::endl;
}

Test::~Test() {
    std::cout << "IMPL DESTRUCTOR!" << std::endl;
}

void Test::Compute() {
    std::string msg = vertex_id() + std::string(" says hi on ") + std::to_string(get_superstep()) + std::string("\n");
    std::cout << msg;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    send_msg(std::string("t1"), 4);
    for (auto m : get_incoming_msg()) {
        std::cout << std::to_string(m) + vertex_id();
    }

    if (get_superstep() == 5) {
        vote_halt();
    }
    increment_superstep();
}

std::vector<Test*> generate_seven_test_nodes() {
    std::vector<Test*> a;
    std::string t1_id = "t1";
    Test * t1 = new Test(t1_id, 1, std::vector<Edge<Test*, int>*>());

    std::string t2_id = "t2";
    Test * t2 = new Test(t2_id, 1, std::vector<Edge<Test*, int>*>());

    std::string t3_id = "t3";
    Test * t3 = new Test(t3_id, 1, std::vector<Edge<Test*, int>*>());

    std::string t4_id = "t4";
    Test * t4 = new Test(t4_id, 1, std::vector<Edge<Test*, int>*>());

    std::string t5_id = "t5";
    Test * t5 = new Test(t5_id, 1, std::vector<Edge<Test*, int>*>());

    std::string t6_id = "t6";
    Test * t6 = new Test(t6_id, 1, std::vector<Edge<Test*, int>*>());

    std::string t7_id = "t7";
    Test * t7 = new Test(t7_id, 1, std::vector<Edge<Test*, int>*>());

    a.push_back(t1);
    a.push_back(t2);
    a.push_back(t3);
    a.push_back(t4);
    a.push_back(t5);
    a.push_back(t6);
    a.push_back(t7);

    return a;
}
