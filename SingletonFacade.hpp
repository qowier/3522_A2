//
// Created by hyper on 2023-11-22.
//

#ifndef LAB1TEMPLATE_SINGLETONFACADE_HPP

#define LAB1TEMPLATE_SINGLETONFACADE_HPP
#define UPPER_BOUND 1000
#define LOWER_BOUND 0

#include <vector>
#include <string>
#include <iostream>
#include <random>
#include <ctime>
#include "City.hpp"

using namespace std;

class SingletonFacade {
private:
    vector<City> master_list;
    vector<Tour> population;

    SingletonFacade() = default;
public:
    static SingletonFacade get_instance();

    void generate_master_list(int size);
};


#endif //LAB1TEMPLATE_SINGLETONFACADE_HPP
