#include "VoltageSource.h"

VoltageSource::VoltageSource(const std::string& id, Node* node1, Node* node2, double voltage)
    : Edge("VoltageSource", id, node1, node2, voltage) {}

std::string VoltageSource::getType() const {
    return "VoltageSource";
}
