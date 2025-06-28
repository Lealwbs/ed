#include "../include/test.hpp"
#include <iostream>

int main(int argc, char** argv) {

    Test::printThing();

    std::cout << argv[1] << std::endl;


    return 0;
}