//
// Created by hyper on 2023-11-22.
//


#include "SingletonFacade.hpp"

SingletonFacade SingletonFacade::get_instance() {
    SingletonFacade sf;
    return sf;
}

void SingletonFacade::generate_master_list(int size) {
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<> distribution(LOWER_BOUND, UPPER_BOUND);

    for(int i = 0; i < size; i++) {
        master_list.emplace_back(to_string(i+65), distribution(generator), distribution(generator));
    }
}

