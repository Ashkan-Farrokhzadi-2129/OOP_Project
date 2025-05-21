cmake_minimum_required(VERSION 3.29)
project(OOP_Project)

set(CMAKE_CXX_STANDARD 23)

# Add include paths for Eigen, Model, and Controller folders
include_directories(
        ${PROJECT_SOURCE_DIR}/external/eigen
        ${PROJECT_SOURCE_DIR}/Model
        ${PROJECT_SOURCE_DIR}/Controller
)

add_executable(OOP_Project
        main.cpp
        Model/Edge.cpp
        Model/Edge.h
        Model/Node.cpp
        Model/Node.h
        Model/Resistor.cpp
        Model/Resistor.h
        Model/Capacitor.cpp
        Model/Capacitor.h
        Model/Inductor.cpp
        Model/Inductor.h
        Model/CurrentSource.cpp
        Model/CurrentSource.h
        Model/VoltageSource.cpp
        Model/VoltageSource.h
        Model/CircuitMatrix.cpp
        Model/CircuitMatrix.h
        Controller/LinearEquationSolver.cpp
        Controller/LinearEquationSolver.h
        Model/CircuitBuilder.cpp
        Model/CircuitBuilder.h
)
