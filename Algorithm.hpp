//
// Created by hyper on 2023-11-24.
//

#ifndef LAB1TEMPLATE_ALGORITHM_HPP
#define LAB1TEMPLATE_ALGORITHM_HPP

#include <iostream>
#include <random>
#include <utility>
#include <memory>

#include "City.hpp"
#include "Tour.hpp"

#define ITERATION_MAX 1000
#define MAP_BOUNDARY  1000
#define MAP_BOUNDARY_LOWER 0
#define POPULATION_SIZE 32
#define PARENT_POOL_SIZE 5
#define MUTATION_RATE 0.15
#define IMPROVEMENT_FACTOR 2.40914
#define NUMBER_OF_ELITES 1

using namespace std;

class Algorithm {
private:
    //Vector of city (master_list)
    vector<City> master_list;

    //Vector of tours to compute.
    vector<Tour *> population;

    //Saves the best distance of the genetic algorithm run
    double best_distance;

    //Base distance used to compare tour distances
    double base_distance;

    double current_improvement;

    // number of elites, can be set differently via setter
    int numberOfElites;

    //TODO, needs set/get
    // the actual number of ’parent’ tours crossed to generate each
    // ’offspring’ tour
    int NUMBER_OF_PARENTS = 0;

public:
    //TODO Constructor
    Algorithm();

    /**
     * Destructor
     */
    ~Algorithm();

    /**
     * Generates a master list of 32 Cities at default.
     */
    void generate_master_list(int size = POPULATION_SIZE);

    /**
     * Generates one single tour by using the master_list internally
     * @param masterList master list of cities
     * @return vector of Tour
     */
    Tour* generate_tour();

    /**
     * Generate a population of tour
     */
    void generate_population();

    /**
     * Getter for population
     * @return vector<Tour *> Tours
     */
    [[nodiscard]] vector<Tour *> getPopulation() const;

    /**
     * Cycles through the population of tours and return the lowest distance
     * rating
     */
    double determine_fitness();

    /**
     * Set the current best fitness with a new fitness (used when found a better fitness)
     * @param new_fitness
     */
    void set_best_fitness(double new_fitness);

    /**
     * Cycles through the population of tours sets the base_distance
     */
    void set_base();

    /**

     * Function to pick the x number of elites.
     * @param numberElite int
     */
    void pickElite();

    /**
     * Calculate genetic algorithm to find the best tour
     */
    void genetic_algorithm();

    // TODO may mutate a tour
    static void mutate(Tour* tour);

    // TODO creates a new tour from a given set of parent tours
    static Tour* crossover(Tour* parent1, Tour* parent2);

    /** Select the parents for a new tour from population
     *
     * @param set1
     * @param set2
     * @return pair<Tour*, Tour*> parents
     */
    static pair<Tour *, Tour *> select_parents(const vector<Tour*>& set1, const vector<Tour*>& set2);

    static int getRandomInt(int min, int max);

    static double getRandomDouble(double min, double max);
};


#endif //LAB1TEMPLATE_ALGORITHM_HPP
