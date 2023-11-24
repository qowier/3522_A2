//
// Created by hyper on 2023-11-22.
//

#ifndef LAB1TEMPLATE_SINGLETONFACADE_HPP

#define LAB1TEMPLATE_SINGLETONFACADE_HPP

#include <vector>
#include <string>
#include <iostream>
#include <random>
#include <ctime>
#include "City.hpp"
#include "Tour.hpp"

using namespace std;

class SingletonFacade {
private:
    vector<City> master_list;
    vector<Tour> population;

    SingletonFacade() = default;
public:
    //Singleton facade for genetic algo.
    static SingletonFacade get_instance();

    //Generates master list of Cities
    void generate_master_list(int size);

    //Starts genetic algorithm steps.
    void run();
};


#endif //LAB1TEMPLATE_SINGLETONFACADE_HPP
