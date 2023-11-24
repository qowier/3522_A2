//
// Created by Haurence on 24/11/2023.
//

#ifndef LAB1TEMPLATE_TOUR_HPP
#define LAB1TEMPLATE_TOUR_HPP

#include "City.hpp"
#include <utility>
#include <vector>
#include <algorithm>
#include <random>

class Tour {
private:
    double fitnessRating{};
    int CITIES_IN_TOURS = 32;
    vector<City *> cityList;
public:
    explicit Tour(const vector<City*>& masterList);

    [[nodiscard]] double getFitnessRating() const;

    void setFitnessRating(double fitnessRating);

    void setCitiesInTours(int citiesInTours);
};


#endif //LAB1TEMPLATE_TOUR_HPP
