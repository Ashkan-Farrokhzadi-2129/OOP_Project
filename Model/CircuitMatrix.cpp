#include "CircuitMatrix.h"
#include "Edge.h"
#include <iostream>
#include "Capacitor.h"
#include "Inductor.h"

CircuitMatrix::CircuitMatrix(int numNodes, int numVoltageSources)
    : n(numNodes), m(numVoltageSources) {
    // Initialize matrices with zeros of correct sizes
    G = Eigen::MatrixXd::Zero(n, n);
    B = Eigen::MatrixXd::Zero(n, m);
    C = Eigen::MatrixXd::Zero(m, n);
    D = Eigen::MatrixXd::Zero(m, m);

    I = Eigen::VectorXd::Zero(m);
    V = Eigen::VectorXd::Zero(n);
    J = Eigen::VectorXd::Zero(n);
    E = Eigen::VectorXd::Zero(m);
}

Eigen::VectorXd CircuitMatrix::solve(LinearEquationSolver& solver) {
    // Construct the MNA matrix
    Eigen::MatrixXd A(n + m, n + m);
    A << G, B,
         C, D;

    // Construct the right hand side vector
    Eigen::VectorXd Z(n + m);
    Z << J,
         E;

    // Solve the linear system A * x = Z using LU decomposition method with full pivoting
    Eigen::VectorXd x = solver.solve(A, Z);

    // Split solution vector into node voltages (V) and currents through voltage sources (I)
    V = x.head(n);
    I = x.tail(m);

    return x;
}

void CircuitMatrix::assemble(const std::vector<Edge*>& edges) {
    for (auto edge : edges) {
        edge->stamp(*this);  // Polymorphic call
    }
}

const int CircuitMatrix::getN() const {
    return n;
}
const int CircuitMatrix::getM() const {
    return m;
}

void CircuitMatrix::updateDynamicComponents(double dt, const Eigen::VectorXd& solution, const std::vector<Edge*>& edges) {
    for (auto edge : edges) {
        if (edge->getType() == "Capacitor") {
            dynamic_cast<Capacitor*>(edge)->updateStamps(dt, *this, solution.head(n));
        }
        else if (edge->getType() == "Inductor") {
            dynamic_cast<Inductor*>(edge)->updateStamps(dt, *this, solution.tail(m));
        }
    }
}

