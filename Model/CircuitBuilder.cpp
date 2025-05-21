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