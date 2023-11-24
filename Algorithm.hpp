//
// Created by hyper on 2023-11-24.
//

#ifndef LAB1TEMPLATE_ALGORITHM_HPP
#define LAB1TEMPLATE_ALGORITHM_HPP
#include <iostream>
#include <random>

#include "City.hpp"
#include "Tour.hpp"
/**
 *
 */


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
    //Vector of tours to compute.
    vector<Tour *> population;

    //Saves the best distance of the genetic algorithm run
    double best_distance;

    //Base distance used to compare tour distances
    double base_distance;

    // number of elites, can be set differently via setter
    int NUMBER_OF_ELITES = 1;

    //TODO, needs set/get
    // the actual number of ’parent’ tours crossed to generate each
    // ’offspring’ tour
    int NUMBER_OF_PARENTS = 0;

public:


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

    /**
     * Cycles through the population of tours sets the base_distance
     */
    void set_base();

    /**
     * Setter for number of elites
     * @param numberOfElites int
     */
    void setNumberOfElites(int numberOfElites);

    /**
     * Function to pick the x number of elites.
     * @param numberElite int
     */
    void pickElite(int numberElite);

    // TODO may mutate a tour
    void mutate();

    // TODO creates a new tour from a given set of parent tours
    void crossover();

    //TODO will select the parents for a new tour from a
    //    population
    void select_parents();
};


#endif //LAB1TEMPLATE_ALGORITHM_HPP
