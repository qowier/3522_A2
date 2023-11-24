//
// Created by Haurence on 24/11/2023.
//

#include "Tour.hpp"

double Tour::getFitnessRating() const {
    return fitnessRating;
}

void Tour::setFitnessRating(double new_fitnessRating) {
    Tour::fitnessRating = new_fitnessRating;
}
