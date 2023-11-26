//
// Created by hyper on 2023-11-24.
//

#include "Algorithm.hpp"

Algorithm::Algorithm()=default;

void Algorithm::generate_master_list(int size) {
//    random_device rd;
//    mt19937 generator(rd());
//    uniform_int_distribution<> distribution(MAP_BOUNDARY_LOWER, MAP_BOUNDARY);

    for(int i = 0; i < size; i++) {
        master_list.emplace_back(to_string(i+65),
                                 getRandomInt(MAP_BOUNDARY_LOWER, MAP_BOUNDARY),
                                 getRandomInt(MAP_BOUNDARY_LOWER, MAP_BOUNDARY));
    }
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

void Algorithm::pickElite(int number_of_elite) {
    int count = 0;
    while (count != number_of_elite) {
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

void Algorithm::setNumberOfElites(int number_of_elites) {
    numberOfElites = number_of_elites;
}

/**
 * Make one tour by using the City of the master_list
 * @return Tour pointer
 */
Tour* Algorithm::generate_tour() {
    return new Tour(master_list);
}

/**
 * Make a population of tours bu using
 * generate_tour function and but it in the population vector
 */
void Algorithm::generate_population() {
    for(int i = 0; i < POPULATION_SIZE; i++) {
        population.emplace_back(generate_tour());
    }
}

vector<Tour *> Algorithm::getPopulation() const {
    return population;
}

//TODO: Make destructor to deallocate city and tour
Algorithm::~Algorithm() {
    for (Tour* tour : population) {
        delete(tour);
    }
}

void Algorithm::genetic_algorithm() {
    /**
     * While(best_fitness / base_fitness < improvement_rate &&
     *       iteration < predetermined_iteration){
     *
     *       find the elite in the population and set it to the front
     *
     *       get parent from the population------
     *          - divide the current population into two sub-population (crosses)
     *                                          \
     *                                          cross over and mutation
     *                                          /
     *       use parents to create new tours-----
     *
     *      check if one of the new tours have better fitness than the current elite.
     *      if (there is better fitness) {
     *          set new best_fitness = better_fitness
     *          set new elite
     *      } else {
     *          print old fitness
     *          print best non-elite from new tours
     *      }
     *
     *      iteration++
     *  }
     */
    int counter = 0;
    vector<Tour *> set1;
    vector<Tour *> set2;
    vector<Tour*> crosses;
    pair<Tour*, Tour*> parents;

    while(base_distance / best_distance < IMPROVEMENT_FACTOR && counter < ITERATION_MAX){
        // Get the first elite and put it at the front
        pickElite();

        for(int i = 0; i < 5; i++) {
            set1.push_back(population[getRandomInt(1, POPULATION_SIZE)]);
        }

        while (set2.size() < 5) {
            Tour* candidate = population[getRandomInt(1, POPULATION_SIZE)];

            // Check if the candidate is not in parent1
            if (std::find(set1.begin(), set1.end(), candidate) == set1.end()) {
                set2.push_back(candidate);
            }
        }

        crosses.push_back(population[0]);

        while (crosses.size() < POPULATION_SIZE){
            parents = select_parents(set1, set2);

            crosses.push_back(crossover(parents.first, parents.second));
        }

        //TODO: Create mutation process

        //TODO: Check for new best_fitness

        counter ++;
    }

}

void Algorithm::mutate() {

}

Tour* Algorithm::crossover(Tour *parent1, Tour *parent2) {
    Tour* t;

    for(int i = 0; i < POPULATION_SIZE/2; i++){
        t->add_city(parent1->getCity(i));
    }

    for(int i = 0; i < POPULATION_SIZE; i++){
        if(!parent1->contains_city(*parent2->getCity(i)));
        t->add_city(parent1->getCity(i));
    }

    return t;
}

pair<Tour *, Tour *> Algorithm::select_parents(const vector<Tour*>& set1, const vector<Tour*>& set2) {
    Tour * p1 = set1[getRandomInt(0, 5)];
    Tour * p2 = set1[getRandomInt(0, 5)];
    return make_pair(p1, p2);
}

int Algorithm::getRandomInt(int min, int max) {
    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(min, max);

    return distrib(gen);
}
