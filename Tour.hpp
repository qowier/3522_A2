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
    double fitnessRating;
    int CITIES_IN_TOURS = 32;
    vector<City *> cityList;
public:
    explicit Tour(const vector<City*>& masterList);

    //Setters and getters
    [[nodiscard]] double getFitnessRating() const;

    void setFitnessRating(double fitnessRating);

    void setCitiesInTours(int citiesInTours);

    /**
   * Returns the distance of the tour.
   * @return totalDistance double
   */
    double get_tour_distance();

    /**
     *  Gets the distance between 2 Cities
     * @param city1
     * @param city2
     * @return cityDistance distance between 2 cities
     */
    double get_distance_between_cities(City* city1, City* city2);

    /**
     * Shuffles the cities in the tour.
     */
    void shuffleCities();

    /**
     * Checks if a tour contains a specific city.
     * @param city City to be searched for
     */
    bool contains_city(const City& city) const;
};


#endif //LAB1TEMPLATE_TOUR_HPP
