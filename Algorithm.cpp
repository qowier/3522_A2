//
// Created by hyper on 2023-11-24.
//

#include "Algorithm.hpp"

Algorithm::Algorithm()=default;

//TODO: Make destructor to deallocate city and tour
Algorithm::~Algorithm() {
    for (Tour* tour : population) {
        delete(tour);
    }
}

void Algorithm::generate_master_list(int size) {
//    random_device rd;
//    mt19937 generator(rd());
//    uniform_int_distribution<> distribution(MAP_BOUNDARY_LOWER, MAP_BOUNDARY);
    char c;
    for(int i = 0; i < size; i++) {
        c = (char)(i+65);
        master_list.emplace_back(to_string(c),
                                 getRandomInt(MAP_BOUNDARY_LOWER, MAP_BOUNDARY),
                                 getRandomInt(MAP_BOUNDARY_LOWER, MAP_BOUNDARY));
    }
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

double Algorithm::determine_fitness() {
    double fittest = population[0]->getFitnessRating();
    for (const Tour* tour : population) {
        if (tour->getFitnessRating() < fittest){
            fittest = tour->getFitnessRating();
        }
    }
    return fittest;
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
    while (count < number_of_elite) {
        double localBest = population[count]->getFitnessRating();
        for (int i = count + 1; i < (int)population.size(); ++i){
            if (population[i]->getFitnessRating() < localBest){
                localBest = population[i]->getFitnessRating();
                swap(population[i], population[count]);
            }
        }
        ++count;
    }
}

void Algorithm::set_best_fitness(double new_fitness) {
    best_distance = new_fitness;
}

void Algorithm::setNumberOfElites(int number_of_elites) {
    numberOfElites = number_of_elites;
}

vector<Tour *> Algorithm::getPopulation() const {
    return population;
}

void Algorithm::mutate(Tour* tour) {
    if(getRandomDouble(0, 1) <= MUTATION_RATE) {
        tour->shuffleCities();
    }
}

Tour* Algorithm::crossover(Tour *parent1, Tour *parent2) {
    // Child tour
    Tour* t = new Tour();

    for(int i = 0; i < POPULATION_SIZE/2; i++){
        t->add_city(parent1->getCity(i));
    }

    for(int i = 0; i < POPULATION_SIZE; i++){
        // Check if the city in parent 2 is already in t
        if(!t->contains_city(*parent2->getCity(i))){
            t->add_city(parent2->getCity(i));
        }
    }
    return t;
}

pair<Tour *, Tour *> Algorithm::select_parents(const vector<Tour*>& set1, const vector<Tour*>& set2) {
    Tour * p1 = set1[getRandomInt(0, 4)];
    Tour * p2 = set2[getRandomInt(0, 4)];
    return make_pair(p1, p2);
}

int Algorithm::getRandomInt(int min, int max) {
    random_device rd;  // Will be used to obtain a seed for the random number engine
    mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    uniform_int_distribution<> distrib(min, max);

    return distrib(gen);
}

double Algorithm::getRandomDouble(double min, double max) {
    default_random_engine generator(time(nullptr));
    uniform_real_distribution<double> distribution(min, max);

    return distribution(generator);
}

void Algorithm::genetic_algorithm() {
    int counter = 0;
    double new_fitness;
    vector<Tour *> set1;
    vector<Tour *> set2;
    vector<Tour*> crosses;
    pair<Tour*, Tour*> parents;
    set_best_fitness(base_distance);

    while(base_distance / best_distance < IMPROVEMENT_FACTOR && counter < ITERATION_MAX){
        // Get the first elite and put it at the front
        pickElite();


        set1.clear();
        // Create set 1 to store 5 tours (use to get parents)
        for(int i = 0; i < 5; i++) {
            set1.push_back(population[getRandomInt(1, POPULATION_SIZE)]);
        }
        set2.clear();
        // Create set 2 to store 5 tours, different from set 1 (use to get parents)
        while (set2.size() < 5) {
            Tour* candidate = population[getRandomInt(1, POPULATION_SIZE)];

            // Check if the candidate is not in parent1
            if (find(set1.begin(), set1.end(), candidate) == set1.end()) {
                set2.push_back(candidate);
            }
        }

        // Put the elite in the front of the crosses
        crosses.insert(crosses.begin(), population[0]);

        // Create new population from crossing two sets above (set1 and set2)
        while (crosses.size() < POPULATION_SIZE){
            // Call selectParent to get a pair of parent from each set
            parents = select_parents(set1, set2);

            // Extract parent 1 and parent 2 to get a new tour and add it to the crosses vector (new population)
            crosses.push_back(crossover(parents.first, parents.second));
        }

        // Perform mutation in the crosses vector (new population)
//        for (size_t i = 1; i < crosses.size(); i++) {
//            mutate(crosses[i]);
//        }

        // Update new population with merged and mutated Tour
        population.clear();
        population = std::move(crosses);

        // Revaluate fitness to find the best_fitness
        new_fitness = determine_fitness();

        if(base_distance / new_fitness >= IMPROVEMENT_FACTOR){
            cout<<"--- FINISHED ALGORITHM ---"<<endl;
            break;
        }else if(new_fitness < best_distance) {
            set_best_fitness(new_fitness);
            cout<<"NEW ELITE FOUND: "<<endl;
            cout<<"Base: "<<base_distance<<endl;
            cout<<"Best: "<<best_distance<<endl<<endl;
//            cout<<"Iteration: "<<counter<<endl;
//            cout<<"NEW ELITE FOUND: "<<endl;
//            cout<<"Distance:"<< best_distance <<endl;
//            cout<<"Improvement over base: "<< base_distance / best_distance <<endl<<endl;
        }else {
            cout<<"Base: "<<base_distance<<endl;
            cout<<"Best: "<<best_distance<<endl<<endl;
            cout<<"Non-elite: "<<new_fitness<<endl<<endl;
//            cout<<"Iteration: "<<counter<<endl;
//            cout<<"Elite Distance: "<< best_distance<<endl;
//            cout<<"Best non-elite distance: "<<new_fitness<<endl;
//            cout<<"Improvement over base: "<< base_distance / best_distance <<endl<<endl;
        }
        counter ++;
    }
}
