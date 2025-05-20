#include "CurrentSource.h"

CurrentSource::CurrentSource(const std::string& id, Node* node1, Node* node2, double current)
    : Edge("CurrentSource", id, node1, node2, current) {}

std::string CurrentSource::getType() const {
    return "CurrentSource";
}
