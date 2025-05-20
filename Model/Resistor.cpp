#include "Resistor.h"

Resistor::Resistor(const std::string& id, Node* node1, Node* node2, double resistance)
    : Edge("Resistor", id, node1, node2, resistance) {}

std::string Resistor::getType() const {
    return "Resistor";
}
