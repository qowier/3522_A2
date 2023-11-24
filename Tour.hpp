//
// Created by Haurence on 24/11/2023.
//

#ifndef LAB1TEMPLATE_TOUR_HPP
#define LAB1TEMPLATE_TOUR_HPP

#include "City.hpp"
#include <vector>

class Tour {
private:
    double fitnessRating;
public:
    double getFitnessRating() const;

    void setFitnessRating(double fitnessRating);

private:
    vector<City *> cityList;

};


#endif //LAB1TEMPLATE_TOUR_HPP
