#ifndef CAPACITOR_H
#define CAPACITOR_H

#include "Edge.h"
#include <string>

class Capacitor : public Edge {
public:
    Capacitor(const std::string& id, Node* node1, Node* node2, double capacitance);

    std::string getType() const override;
    void stamp(CircuitMatrix& matrix) override;

    // For time-domain analysis
    void updateStamps(double dt, CircuitMatrix& matrix, const Eigen::VectorXd& voltages);

private:
    double prevCurrent = 0.0;
    double prevVoltage = 0.0;
};

#endif // CAPACITOR_H
