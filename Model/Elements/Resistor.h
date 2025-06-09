#ifndef OOP_PROJECT_RESISTOR_H
#define OOP_PROJECT_RESISTOR_H

#include "Edge.h"

class Resistor : public Edge {
public:
    Resistor(const std::string& id, Node* node1, Node* node2, double resistance);

    // Optional: you can override methods if needed
    std::string getType() const override;

    void stamp(CircuitMatrix& matrix) override;
    void updateStamps(double dt, CircuitMatrix& matrix,
                     const Eigen::VectorXd& solution) override;

    std::string getInfoString() const override;
    double getCurrent(const Eigen::VectorXd& state) const override;
};

#endif // OOP_PROJECT_RESISTOR_H
