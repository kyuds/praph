#include "engine.hh"
#include "pregel.hh"
#include "algo/test.hh"

#include <iostream>
#include <chrono>

int main(int argc, char *argv[]) {
    PregelEngine<Test> * e = new PregelEngine<Test>(generate_seven_test_nodes(), 5);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    e->run();

    std::cout << "done joining" << std::endl;

    delete e;
    return 0;
}
