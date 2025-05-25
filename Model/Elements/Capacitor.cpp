#include "Capacitor.h"

Capacitor::Capacitor(const std::string& id, Node* node1, Node* node2, double capacitance)
    : Edge("Capacitor", id, node1, node2, capacitance) {}

std::string Capacitor::getType() const {
    return "Capacitor";
}
