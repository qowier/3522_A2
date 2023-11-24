//
// Created by hyper on 2023-11-24.
//

#include "Algorithm.hpp"

Algorithm::Algorithm()=default;

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
    best_distance = fittest;
}

void Algorithm::set_base() {
    double fittest = population[0]->getFitnessRating();
    for (const Tour* tour : population) {
        if (tour->getFitnessRating() < fittest){
            fittest = tour->getFitnessRating();
        }
    }
    base_distance = fittest;
}

void Algorithm::pickElite(int NUMBER_OF_ELITES) {
    int count = 0;
    while (count != NUMBER_OF_ELITES) {
        for (int i = count; i < (int)population.size(); ++i){
            double localBest = population[count]->getFitnessRating();
            if (population[i]->getFitnessRating() < localBest){
                localBest = population[i]->getFitnessRating();
                std::swap(population[i], population[count]);
            }
        }
        ++count;
    }
}

void Algorithm::setNumberOfElites(int numberOfElites) {
    NUMBER_OF_ELITES = numberOfElites;
}

vector<Tour> Algorithm::generate_init_tours() {
    return vector<Tour>();
}

vector<Tour> Algorithm::generate_init_tours(const vector<City*>& masterList) {
    for (int i = 0; i < masterList.size() -1 ; ++i) {
        Tour *newTour = new Tour(masterList);
        population.push_back(newTour);
    }
    return{};
}

const vector<Tour *> Algorithm::getPopulation() const {
    return population;
}
