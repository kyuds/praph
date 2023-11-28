#include "engine.hh"
#include "pregel.hh"
#include "algo/pagerank.hh"

#include <iostream>
#include <chrono>

int main(int argc, char *argv[]) {
    PregelEngine<PageRankVertex> * e = new PregelEngine<PageRankVertex>(generate_graph(), 5);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    e->run();

    std::cout << "done joining" << std::endl;

    delete e;
    return 0;
}
