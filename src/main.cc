#include <iostream>
#include <stdexcept>

int main(int argc, char *argv[]) {
    if (argc == 1) {
        throw std::invalid_argument("Need to specify algorithm.");
    }

    // add new algos here:

    std::cout << "Running " << argv[1] << std::endl;

    return 0;
}