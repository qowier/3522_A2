//Name: Haurence Li
//Student# : A01320705
//Name: Viet Hai Nguyen
//Student ID: A01320311
//Set: 3B

#include <iostream>
#include "SingletonFacade.hpp"

/*
 * Drives program.
 */
int main() {
    std::cout << "Assignment 2, Hello, World!" << std::endl;

    //Instantiate singleton
    SingletonFacade sf = SingletonFacade->get_instance();

    //Run genetic algorithm.
    sf.run();

    return 0;
}
