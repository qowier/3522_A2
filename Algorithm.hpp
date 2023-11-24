//
// Created by hyper on 2023-11-24.
//

#ifndef LAB1TEMPLATE_ALGORITHM_HPP
#define LAB1TEMPLATE_ALGORITHM_HPP
#include <iostream>
#include <random>

#include "City.hpp"
#include "Tour.hpp"

#define ITERATION_MAX 1000
#define MAP_BOUNDARY  1000
#define MAP_BOUNDARY_LOWER 0
//TODO the number of members randomly selected from the population
//when choosing a parent, from which the fittest is made a ’parent’
#define  PARENT_POOL_SIZE 5
//TODO NICE TO HAVE
//probably low like 15 percent but it would be nice if the user can choose
#define MUTATION_RATE 0.15
#define IMPROVEMENT_FACTOR 2.40914
#define POPULATION_SIZE 32


class Algorithm {
private:
    //Saves the best distance of
    double best_distance;
    double base_distance;
    vector<Tour *> population;
    //TODO, needs set/get
    // the actual number of ’parent’ tours crossed to generate each
    // ’offspring’ tour
    int NUMBER_OF_PARENTS = 0;
    //TODO, needs set/get
    // the actual number of ’parent’ tours crossed to generate each
    // ’offspring’ tour
    int NUMBER_OF_ELITES = 1;


public:
    //TODO Constructor
    Algorithm();

    /**
     * Generates a master list of 32 Cities.
     * @return vector<City>
     */
    vector<City> generate_master_list();

    /**
     * Cycles through the population of tours and saves the lowest distance
     * rating as the base_distance
     */
    void determine_fitness();

    //TODO will select the parents for a new tour from a
    //    population
    void select_parents();

    // TODO creates a new tour from a given set of parent tours
    void crossover();

    // TODO may mutate a tour
    void mutate();

};


#endif //LAB1TEMPLATE_ALGORITHM_HPP
