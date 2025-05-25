#ifndef TIMESOLVER_H
#define TIMESOLVER_H

#include <vector>
#include <functional>
#include <Eigen/Dense>

class TimeSolver {
public:
    TimeSolver(double dt);
    
    // Solve differential equation dy/dt = f(t, y)
    Eigen::VectorXd solve(
        double t, 
        const Eigen::VectorXd& y,
        std::function<Eigen::VectorXd(double, const Eigen::VectorXd&)> f);
    
    double getTimeStep() const { return dt; }
    void setTimeStep(double new_dt) { dt = new_dt; }

private:
    double dt; // time step
};

#endif // TIMESOLVER_H