//Name: Haurence Li
//Student# : A01320705
//Name: Viet Hai Nguyen
//Student ID: A01320311
//Set: 3B

#include <iostream>
#include "SingletonFacade.hpp"

/*
 * Drives program.
 */
int main() {

    //Instantiate singleton
    SingletonFacade::get_instance().run();

    return 0;
}
