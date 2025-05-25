cmake_minimum_required(VERSION 3.29)
project(OOP_Project)

set(CMAKE_CXX_STANDARD 23)

# Add include paths for Eigen, Model, Model/Elements, Model/Solvers, View, and Controller folders
include_directories(
        ${PROJECT_SOURCE_DIR}/external/eigen
        ${PROJECT_SOURCE_DIR}/Model
        ${PROJECT_SOURCE_DIR}/Model/Elements
        ${PROJECT_SOURCE_DIR}/Model/Solvers
        ${PROJECT_SOURCE_DIR}/View
        ${PROJECT_SOURCE_DIR}/Controller
)

add_executable(OOP_Project
        main.cpp
        Model/CircuitBuilder.cpp
        Model/CircuitBuilder.h
        Model/CircuitMatrix.cpp
        Model/CircuitMatrix.h
        Model/Edge.cpp
        Model/Edge.h
        Model/Node.cpp
        Model/Node.h
        Model/Elements/Resistor.cpp
        Model/Elements/Resistor.h
        Model/Elements/Capacitor.cpp
        Model/Elements/Capacitor.h
        Model/Elements/Inductor.cpp
        Model/Elements/Inductor.h
        Model/Elements/CurrentSource.cpp
        Model/Elements/CurrentSource.h
        Model/Elements/VoltageSource.cpp
        Model/Elements/VoltageSource.h
        Model/Solvers/LinearEquationSolver.cpp
        Model/Solvers/LinearEquationSolver.h
        View/InputError.cpp
        View/InputError.h
        Controller/InputParser.cpp
        Controller/InputParser.h
        Model/Solvers/TimeSolver.cpp
        Model/Solvers/TimeSolver.h
)