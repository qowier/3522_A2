//
// Created by hyper on 2023-11-24.
//

#include "Algorithm.hpp"

Algorithm::Algorithm() {
    best_distance = INT_MAX;
    base_distance = INT_MAX;
    current_improvement = 0;
};

Algorithm::~Algorithm() {
    for (Tour* tour : population) {
        delete(tour);
    }
}

void Algorithm::generate_master_list(int size) {
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

void Algorithm::pickElite() {
    double elite_fitness = determine_fitness();

    for (int i = 0; i < POPULATION_SIZE; i++) {
        if(population[i]->getFitnessRating() == elite_fitness) {
            swap(population[i], population[0]);
        }
    }
}

void Algorithm::set_best_fitness(double new_fitness) {
    best_distance = new_fitness;
}

vector<Tour *> Algorithm::getPopulation() const {
    return population;
}

void Algorithm::mutate(Tour* tour) {
    for (size_t i = 0; i < tour->get_city_list().size()-1; i++) {
        if (getRandomDouble(0, 1) <= MUTATION_RATE) {
            swap(tour->get_city_list()[i], tour->get_city_list()[(i + 1) % tour->get_city_list().size()]);
        }
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
    double new_fitness = 0;
    vector<Tour *> set1;
    vector<Tour *> set2;
    vector<Tour*> crosses;
    pair<Tour*, Tour*> parents;

    // Best_fitness will equal to base initially
    set_best_fitness(base_distance);

    while(base_distance / best_distance < IMPROVEMENT_FACTOR && counter < ITERATION_MAX){
        // Get the first elite in population and swaps to front.
        pickElite();

        //Reset all vector<Tour*>
        crosses.clear();
        set1.clear();
        set2.clear();

        // Create set 1 to store 5 tours (use to get parents)
        for(int i = 0; i < PARENT_POOL_SIZE; i++) {
            set1.push_back(population[getRandomInt(1, POPULATION_SIZE)]);
        }

        // Create set 2 to store 5 tours, different from set 1 (use to get parents)
        while (set2.size() < PARENT_POOL_SIZE) {
            Tour* candidate = population[getRandomInt(1, POPULATION_SIZE)];

            // Check if the candidate is not in parent1
            if (find(set1.begin(), set1.end(), candidate) == set1.end()) {
                set2.push_back(candidate);
            }
        }

        // Put the elite in the front of the crosses
        crosses.push_back(population[0]);

        // Create new population from crossing two sets above (set1 and set2)
        while (crosses.size() - 1 < POPULATION_SIZE){
            // Call selectParent to get a pair of parent from each set
            parents = select_parents(set1, set2);

            // Extract parent 1 and parent 2 to get a new tour and add it to the crosses vector (new population)
            crosses.push_back(crossover(parents.first, parents.second));
        }

        // Perform mutation in the crosses vector (new population)
        for (size_t i = 1; i < crosses.size(); i++) {
            mutate(crosses[i]);
        }

        // Update new population with merged and mutated Tour
        population.clear();
        population.assign(crosses.begin(), crosses.end());
        //crosses.clear();

        // Revaluate fitness to find the best_fitness
        new_fitness = determine_fitness();


        if(new_fitness < best_distance) {
            set_best_fitness(new_fitness);
            cout<<"Iteration: "<<counter + 1 <<endl;
            cout<<"NEW ELITE FOUND: "<<endl;
            cout<<"Distance:"<< best_distance <<endl;
            cout<<"Improvement over base: "<< base_distance / best_distance <<endl<<endl;
        }else {
            cout<<"Iteration: "<<counter + 1 <<endl;
            cout<<"Elite Distance: "<< best_distance<<endl;
            cout<<"Best non-elite distance: "<<new_fitness<<endl;
            cout<<"Improvement over base: "<< base_distance / best_distance <<endl<<endl;
        }
        counter ++;
    }

    cout<<"--- FINISHED ALGORITHM ---"<<endl;
    cout<<"Total iterations: "<<counter<<endl;
}
