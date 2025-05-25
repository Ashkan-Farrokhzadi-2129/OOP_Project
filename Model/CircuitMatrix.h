#ifndef CIRCUITMATRIX_H
#define CIRCUITMATRIX_H

// #include <Eigen/Dense>
// #include "Edge.h"
class Edge;
#include "LinearEquationSolver.h"

class CircuitMatrix {
public:
    CircuitMatrix(int numNodes, int numVoltageSources);

    // Matrices in MNA
    Eigen::MatrixXd G; // n x n
    Eigen::MatrixXd B; // n x m
    Eigen::MatrixXd C; // m x n
    Eigen::MatrixXd D; // m x m

    // Vectors
    Eigen::VectorXd I; // m x 1
    Eigen::VectorXd V; // n x 1 (node voltages)
    Eigen::VectorXd J; // n x 1 (current injections)
    Eigen::VectorXd E; // m x 1 (voltage sources)

    // Function to assemble the matrices and vectors (to be implemented)
    void assemble(const std::vector<Edge*>& edges);

    // Solve system using external solver
    Eigen::VectorXd solve(LinearEquationSolver& solver);

    const int getN() const;
    const int getM() const;

    void resetDynamicComponents();
    void updateDynamicComponents(double dt, const Eigen::VectorXd& solution, const std::vector<Edge*>& edges);
private:
    int n; // number of nodes
    int m; // number of voltage sources
};

#endif // CIRCUITMATRIX_H
