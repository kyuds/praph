#include "engine.hh"
#include "pregel.hh"
#include "algos/test.hh"

#include <iostream>

int main(int argc, char *argv[]) {
    PregelEngine<Test> * e = new PregelEngine<Test>(generate_five_test_nodes(), 5);
    e->run();

    std::cout << "done joining" << std::endl;
    return 0;
}