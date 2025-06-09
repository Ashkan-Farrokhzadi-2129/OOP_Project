#include "Resistor.h"
#include "Node.h"

Resistor::Resistor(const std::string& id, Node* node1, Node* node2, double resistance)
    : Edge("Resistor", id, node1, node2, resistance) {}

std::string Resistor::getType() const {
    return "Resistor";
}

void Resistor::stamp(CircuitMatrix& matrix) {
    double g = 1.0 / value;
    int n1 = node1->getNumber();
    int n2 = node2->getNumber();

    if (n1 != 0)
        matrix.G(n1 - 1, n1 - 1) += g;
    if (n2 != 0)
        matrix.G(n2 - 1, n2 - 1) += g;
    if (n1 != 0 && n2 != 0) {
        matrix.G(n1 - 1, n2 - 1) -= g;
        matrix.G(n2 - 1, n1 - 1) -= g;
    }
}


void Resistor::updateStamps(double dt, CircuitMatrix& matrix,
                     const Eigen::VectorXd& solution) {
    // Resistors have no dynamic behavior, so do nothing
}

std::string Resistor::getInfoString() const {
    return id + " " +
           std::to_string(node1->getNumber()) + " " +
           std::to_string(node2->getNumber()) + " " +
           std::to_string(value);
}



double Resistor::getCurrent(const Eigen::VectorXd& state) const {
    int n1 = node1->getNumber();
    int n2 = node2->getNumber();
    return (state(n1) - state(n2)) / value;
}