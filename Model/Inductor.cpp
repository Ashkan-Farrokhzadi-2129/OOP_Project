#include "Inductor.h"

Inductor::Inductor(const std::string& id, Node* node1, Node* node2, double inductance)
    : Edge("Inductor", id, node1, node2, inductance) {}

std::string Inductor::getType() const {
    return "Inductor";
}
