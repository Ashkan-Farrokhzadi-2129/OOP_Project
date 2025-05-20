#include "CircuitMatrix.h"
#include <iostream>

CircuitMatrix::CircuitMatrix(int numNodes, int numVoltageSources)
    : n(numNodes), m(numVoltageSources) {
    // Initialize matrices with zeros of correct sizes
    G = Eigen::MatrixXd::Zero(n, n);
    B = Eigen::MatrixXd::Zero(n, m);
    C = Eigen::MatrixXd::Zero(m, n);
    D = Eigen::MatrixXd::Zero(m, m);

    I = Eigen::VectorXd::Zero(n);
    V = Eigen::VectorXd::Zero(n);
    J = Eigen::VectorXd::Zero(n);
    E = Eigen::VectorXd::Zero(m);
}

Eigen::VectorXd CircuitMatrix::solve() {
    // Construct the MNA matrix
    Eigen::MatrixXd A(n + m, n + m);
    A << G, B,
         C, D;

    // Construct the right hand side vector
    Eigen::VectorXd Z(n + m);
    Z << J,
         E;

    // Solve the linear system A * x = Z
    Eigen::VectorXd x = A.fullPivLu().solve(Z);

    // Split solution vector into node voltages (V) and currents through voltage sources (I)
    V = x.head(n);
    I = x.tail(m);

    return x;
}
