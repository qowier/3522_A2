//
// Created by Haurence on 24/11/2023.
//

#include "Tour.hpp"

double Tour::getFitnessRating() const {
    return fitnessRating;
}

//Setter for fitness rating.
void Tour::setFitnessRating(double new_fitnessRating) {
    Tour::fitnessRating = new_fitnessRating;
}

//Setter for cities in tours, default at 32
void Tour::setCitiesInTours(int citiesInTours) {
    CITIES_IN_TOURS = citiesInTours;
}
