#include "LinearEquationSolver.h"

Eigen::VectorXd LinearEquationSolver::solve(const Eigen::MatrixXd& A, const Eigen::VectorXd& b) {
    // Using LU decomposition as the solver method
    return A.fullPivLu().solve(b);
}
