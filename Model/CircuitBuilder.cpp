#include "CircuitBuilder.h"

CircuitBuilder::CircuitBuilder() : voltageSourceCount(0) {}

Node* CircuitBuilder::getOrCreateNode(int nodeNumber) {
    auto it = nodes.find(nodeNumber);
    if (it != nodes.end()) {
        return it->second;
    }
    Node* node = new Node(nodeNumber);
    nodes[nodeNumber] = node;
    return node;
}

void CircuitBuilder::addResistor(const std::string& id, int n1, int n2, double value) {
    Node* node1 = getOrCreateNode(n1);
    Node* node2 = getOrCreateNode(n2);
    edges.push_back(new Resistor(id, node1, node2, value));
}

void CircuitBuilder::addVoltageSource(const std::string& id, int n1, int n2, double value) {
    Node* node1 = getOrCreateNode(n1);
    Node* node2 = getOrCreateNode(n2);
    edges.push_back(new VoltageSource(id, node1, node2, value, voltageSourceCount));
    voltageSourceCount++;
}

void CircuitBuilder::addCurrentSource(const std::string& id, int n1, int n2, double value) {
    Node* node1 = getOrCreateNode(n1);
    Node* node2 = getOrCreateNode(n2);
    edges.push_back(new CurrentSource(id, node1, node2, value));
}

CircuitMatrix CircuitBuilder::buildMatrix() {
    CircuitMatrix matrix(static_cast<int>(nodes.size()), voltageSourceCount);
    matrix.assemble(edges);
    return matrix;
}


// In CircuitBuilder.cpp
bool CircuitBuilder::resistorExists(const std::string& id) const {
    for (const auto& edge : edges) {
        if (edge->getType() == "Resistor" && edge->getId() == id)
            return true;
    }
    return false;
}

void CircuitBuilder::deleteResistor(const std::string& id) {
    auto it = std::remove_if(edges.begin(), edges.end(),
        [&](Edge* edge) {
            if (edge->getType() == "Resistor" && edge->getId() == id) {
                delete edge;
                return true;
            }
            return false;
        });
    edges.erase(it, edges.end());
}