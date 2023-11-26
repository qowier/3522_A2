//
// Created by Haurence on 24/11/2023.
//

#include "Tour.hpp"

double Tour::getFitnessRating() const {
    return get_tour_distance();
}

//Setter for fitness rating.
void Tour::setFitnessRating(double new_fitnessRating) {
    Tour::fitnessRating = new_fitnessRating;
}

//Setter for cities in tours, default at 32
void Tour::setCitiesInTours(int citiesInTours) {
    CITIES_IN_TOURS = citiesInTours;
}

Tour::Tour(const vector<City> &masterList) {
    default_random_engine defaul_ran(0);
    for(City city : masterList){
        cityList.push_back(&city);
    }
    shuffle(this->cityList.begin(), this->cityList.end(), defaul_ran);
}

void Tour::shuffleCities() {
    default_random_engine defaul_ran(0);
    shuffle(this->cityList.begin(), this->cityList.end(), defaul_ran);
}

double Tour::get_distance_between_cities(City* city1, City* city2) {
    double sumX = pow((city1->x - city2->x) ,2);
    double sumY = pow((city1->y - city2->y) ,2);

    return sqrt(sumX+sumY);
}

double Tour::get_tour_distance() const{
    double totalDistance = 0.0;
    for (size_t i = 0; i < cityList.size() - 1; ++i) {
        totalDistance += get_distance_between_cities(cityList[i], cityList[i + 1]);
    }
    totalDistance += get_distance_between_cities(cityList.back(), cityList.front());
    return totalDistance;
}

bool Tour::contains_city(const City& city) const {
    for (const City *tourCity: cityList) {
        if (city.name == tourCity->name) {
            return true;
        }
    }
    return false; // City not found in the tour
}

void Tour::add_city(City *new_city) {
    this->cityList.push_back(new_city);
}

City *Tour::getCity(int index) {
    return cityList[index];
}


