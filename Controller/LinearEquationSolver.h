#ifndef LINEAREQUATIONSOLVER_H
#define LINEAREQUATIONSOLVER_H

#include <Eigen/Dense>

class LinearEquationSolver {
public:
    // Solve Ax = b, return x
    Eigen::VectorXd solve(const Eigen::MatrixXd& A, const Eigen::VectorXd& b);

    // You can add more methods later if needed
};

#endif // LINEAREQUATIONSOLVER_H
