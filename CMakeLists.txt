cmake_minimum_required(VERSION 3.20)
project(lab1template)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
set(CMAKE_CXX_STANDARD 20)

add_executable(
        assignment2template
        main.cpp
        City.cpp
        City.hpp
        Tour.cpp
        Tour.hpp
        Algorithm.cpp
        Algorithm.hpp
        SingletonFacade.hpp
        SingletonFacade.cpp)
