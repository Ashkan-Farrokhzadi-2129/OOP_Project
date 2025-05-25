#include "TimeSolver.h"
#include <iostream>

TimeSolver::TimeSolver(double dt) : dt(dt) {}

Eigen::VectorXd TimeSolver::solve(
    double t, 
    const Eigen::VectorXd& y,
    std::function<Eigen::VectorXd(double, const Eigen::VectorXd&)> f) {
    
    // Using trapezoidal integration (2nd order accurate)
    Eigen::VectorXd k1 = f(t, y);
    Eigen::VectorXd k2 = f(t + dt, y + dt * k1);
    
    return y + (dt/2.0) * (k1 + k2);
}