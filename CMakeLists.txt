cmake_minimum_required(VERSION 3.25)
project(hotel)

set(CMAKE_CXX_STANDARD 23)

include_directories(.)

add_executable(hotel
        header.hpp
        main.cpp
        module.cpp
        )
