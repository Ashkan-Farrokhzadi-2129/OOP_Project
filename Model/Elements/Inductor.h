#ifndef INDUCTOR_H
#define INDUCTOR_H

#include "Edge.h"
#include <string>

class Inductor : public Edge {
public:
    Inductor(const std::string& id, Node* node1, Node* node2, double inductance);

    std::string getType() const override;
    void stamp(CircuitMatrix& matrix) override;

    // For time-domain analysis
    void updateStamps(double dt, CircuitMatrix& matrix, const Eigen::VectorXd& currents) override;

    std::string getInfoString() const override;

private:
    double prevCurrent = 0.0;
    double prevVoltage = 0.0;
};

#endif // INDUCTOR_H
