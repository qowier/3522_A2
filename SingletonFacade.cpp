//
// Created by hyper on 2023-11-22.
//

#include "Tour.hpp"
#include "Algorithm.hpp"
#include "SingletonFacade.hpp"


SingletonFacade SingletonFacade::get_instance() {
    SingletonFacade sf;
    return sf;
}

void SingletonFacade::run() {
    /*
     *  while loop (termination criteria not reached) {
     *      determine_fitness (selects the best of current tour)
     *      pickElite(); (swap bests to proper top-of-list)
     *      selectParents(); //grabs elites and crossover
     *          -> calls crossover();
     *      mutate(); //
     *      exitLoopCheck();
     *  }
     */
}
