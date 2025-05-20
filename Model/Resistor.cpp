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