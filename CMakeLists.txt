cmake_minimum_required(VERSION 3.29)
project(OOP_Project)

set(CMAKE_CXX_STANDARD 23)

add_executable(OOP_Project main.cpp
        Model/Edge.cpp
        Model/Edge.h
        Model/Node.cpp
        Model/Node.h)
