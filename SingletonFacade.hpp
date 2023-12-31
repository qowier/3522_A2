//
// Created by hyper on 2023-11-22.
//

#ifndef LAB1TEMPLATE_SINGLETONFACADE_HPP

#define LAB1TEMPLATE_SINGLETONFACADE_HPP

#include <vector>
#include <iostream>
#include <string>
#include "Algorithm.hpp"

using namespace std;

class SingletonFacade {
private:
    Algorithm algo;
    SingletonFacade() = default;
public:
    //Singleton facade for genetic algo.
    static SingletonFacade get_instance();

    //Starts genetic algorithm steps.
    void run();
};


#endif //LAB1TEMPLATE_SINGLETONFACADE_HPP
