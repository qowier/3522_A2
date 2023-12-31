//
// Created by Haurence on 24/11/2023.
//

#include "Tour.hpp"

#include <utility>
#include <sstream>

Tour::Tour(const vector<City> &masterList) {
    std::random_device rd;
    std::mt19937 gen(rd());
    for(const City& city : masterList){
        cityList.push_back(new City(city));
    }
    std::shuffle(this->cityList.begin(), this->cityList.end(), gen);
    fitnessRating = get_tour_distance();
}

double Tour::getFitnessRating() const {
    return fitnessRating;
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
        if (city.name == tourCity->name && city.x == tourCity->x && city.y == tourCity->y) {
            return true;
        }
    }
    return false; // City not found in the tour
}

void Tour::add_city(City *new_city) {
    this->cityList.push_back(new_city);
}

City * Tour::getCity(int index) const {
    return cityList[index];
}

void Tour::setCity(int index, City * newCity) {
    if (index >= 0 && index < cityList.size()) {
        cityList[index] = newCity;
    } else {
        if (index >= cityList.size()) {
            cityList.resize(index + 1);
        }
        cityList[index] = newCity;
    }
}

vector<City *> Tour::get_city_list() const {
    return this->cityList;
}

void Tour::setFitnessRating(double fr) {
    fitnessRating = fr;
}

void Tour::set_city_list(vector<City *> new_list) {
    this->cityList = std::move(new_list);
}

int Tour::getCitiesInTours() const {
    return CITIES_IN_TOURS;
}

std::string Tour::toString() const {
    std::stringstream ss;
    ss << "Tour: [";
    for (int i = 0; i < (int) get_city_list().size(); ++i) {
        if (i > 0) {
            ss << " -> ";
        }
        ss << getCity(i)->getName(); // Assuming City has a getName() method
    }
    ss << "]";
    return ss.str();
}



