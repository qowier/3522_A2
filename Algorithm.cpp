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
    for (size_t i = 0; i < tour->get_city_list().size(); i++) {
        if (((double)getRandomInt(0, 100) / 100) <= MUTATION_RATE) {
            City* currentCity = tour->getCity(i);
            City* nextCity = (i == tour->get_city_list().size() - 1) ? tour->getCity(0) : tour->getCity(i + 1);

            // Swap the cities
            tour->setCity((int) i, nextCity);
            tour->setCity((i == tour->get_city_list().size() - 1) ? 0 : (int)
            i + 1, currentCity);
        }
    }
}

Tour* Algorithm::crossover(Tour *parent1, Tour *parent2) {
    // Child tour
    Tour* t = new Tour();
    vector<City*> new_list;
    for(int i = 0; i < POPULATION_SIZE/2; i++){
        new_list.push_back(parent1->getCity(i));
    }

    for(int i = 0; i < POPULATION_SIZE; i++){
        // Check if the city in parent2 is already in new_list
        auto it = find(new_list.begin(), new_list.end(), parent2->getCity(i));
        if(it == new_list.end()) {
            new_list.push_back(parent2->getCity(i));
        }
    }
    t->set_city_list(new_list);
    t->setFitnessRating(t->get_tour_distance());

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

    //Prepare output for original list
    pickElite();
    string ogList = population[0]->toString();

    // Best_fitness will equal to base initially
    set_best_fitness(base_distance);

    while(current_improvement < IMPROVEMENT_FACTOR && counter < ITERATION_MAX){
        // Get the first elite in population and swaps to front.
        pickElite();

        //Reset all vector<Tour*>
        crosses.clear();
        set1.clear();
        set2.clear();

        // Create set 1 to store 5 tours (use to get parents)
        for (int i = 0; i < PARENT_POOL_SIZE; i++) {
            set1.push_back(population[getRandomInt(0, POPULATION_SIZE - 1)]);
        }

        // Create set 2 to store 5 tours, different from set 1 (use to get parents)
        while (set2.size() < PARENT_POOL_SIZE) {
            Tour* candidate = population[getRandomInt(0, POPULATION_SIZE - 1)];

            if (find(set1.begin(), set1.end(), candidate) == set1.end() &&
                find(set2.begin(), set2.end(), candidate) == set2.end()) {
                set2.push_back(candidate);
            }

            // Break out of the loop if set2 cannot reach PARENT_POOL_SIZE without duplicates
            if (set2.size() + set1.size() >= POPULATION_SIZE) {
                break;
            }
        }

        // Put the elite in the front of the crosses
        crosses.push_back(population[0]);

        // Create new population from crossing two sets above (set1 and set2)
        while (crosses.size() < POPULATION_SIZE){
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

        // Revaluate fitness to find the best_fitness
        new_fitness = determine_fitness();
        current_improvement = base_distance / best_distance;


        if(new_fitness < best_distance) {
            set_best_fitness(new_fitness);
            cout<<"Iteration: "<< counter + 1 <<endl;
            cout<<"NEW ELITE FOUND!" <<endl;
            cout<<"Distance:"<< best_distance <<endl;
            cout<<"Current improvement over base: "<< current_improvement
            <<endl<<endl;
        }else {
            cout<<"Iteration: "<< counter + 1 << endl;
            cout<<"Elite Distance: "<< best_distance <<endl;
            cout<<"Best non-elite distance: "<< crosses[0]->getFitnessRating() << endl;
            cout<<"Current improvement over base: "<< current_improvement <<endl<<endl;
        }
        counter ++;
    }

    //Final output.
    cout<<"--- FINISHED ALGORITHM ---"<< endl
        << "Total iterations: "<< counter + 1 << endl
        <<"Original Elite: " << endl
        <<"Distance: " << base_distance << endl
        << ogList <<endl<<endl;

    cout<<"Best Elite: " << endl
        <<"Distance: " << population[0]->getFitnessRating() <<endl
        << population[0]->toString() << endl<<endl;

    cout<<"Improvement reached!"<<endl;
    cout<<"Improvement factor: "<< current_improvement;
}
