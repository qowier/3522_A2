//
// Created by hyper on 2023-11-22.
//

#ifndef LAB1TEMPLATE_SINGLETONFACADE_HPP

#define LAB1TEMPLATE_SINGLETONFACADE_HPP

#include <vector>
#include <string>
#include <ctime>
#include "City.hpp"
#include "Tour.hpp"
#include "Algorithm.hpp"

using namespace std;

class SingletonFacade {
private:
    vector<City> master_list;
    vector<Tour> population;
    Algorithm algo;
    SingletonFacade() = default;
public:
    //Singleton facade for genetic algo.
    static SingletonFacade get_instance();

    //Starts genetic algorithm steps.
    void run();
};


#endif //LAB1TEMPLATE_SINGLETONFACADE_HPP
