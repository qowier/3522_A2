//
// Created by Haurence on 24/11/2023.
//

#ifndef LAB1TEMPLATE_TOUR_HPP
#define LAB1TEMPLATE_TOUR_HPP

#include "City.hpp"
#include <utility>
#include <vector>

class Tour {
private:
    double fitnessRating{};

    vector<City *> cityList;
public:
    Tour(vector<City*> masterList) : cityList(std::move(masterList)){}

    [[nodiscard]] double getFitnessRating() const;

    void setFitnessRating(double fitnessRating);

};


#endif //LAB1TEMPLATE_TOUR_HPP
