//
// Created by hyper on 2023-11-24.
//

#include "Algorithm.hpp"
vector<City> Algorithm::generate_master_list() {
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<> distribution(MAP_BOUNDARY_LOWER, MAP_BOUNDARY);
    vector <City> master_list;

    for(int i = 0; i < POPULATION_SIZE; i++) {
        master_list.emplace_back(to_string(i+65), distribution(generator), distribution(generator));
    }

    return master_list;
}

void Algorithm::determine_fitness() {
    double fittest = population[0]->getFitnessRating();
    for (const Tour* tour : population) {
        if (tour->getFitnessRating() < fittest){
            fittest = tour->getFitnessRating();
        }
    }
    base_distance = fittest;
}

