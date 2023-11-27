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
    // Creat cities and place them in one master list
    algo.generate_master_list();

    // Use the master list to create tours and place them in population vector
    algo.generate_population();

    // Set the base fitness
    algo.set_base();

    // Run genetic algorithm
    algo.genetic_algorithm();
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
