//
// Created by hyper on 2023-11-22.
//

#ifndef LAB1TEMPLATE_CITY_HPP
#define LAB1TEMPLATE_CITY_HPP

#include <string>
#include <utility>

using namespace std;
class City {
public:
    string name;
    int x;
    int y;

    City(string name, int x, int y) : name(std::move(name)), x(x), y(y){};

    ~City() = default;
};


#endif //LAB1TEMPLATE_CITY_HPP
