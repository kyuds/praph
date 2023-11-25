#include <string>

#include "vertex.hh"
#include "algos/test.hh"

int main(int argc, char *argv[]) {
    std::string name = "name";

    Test * hi = new Test(name, 5, std::vector<int*>());

    delete hi;

    //Vertex<int, int, int> * v = new Vertex<int, int, int>(name, 5, std::vector<int*>());

    return 0;
}