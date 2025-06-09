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

void CircuitBuilder::setGroundNode(int nodeNumber) {
    groundNode = nodeNumber;
}

void CircuitBuilder::addCapacitor(const std::string& id, int n1, int n2, double capacitance) {
    Node* node1 = getOrCreateNode(n1);
    Node* node2 = getOrCreateNode(n2);
    edges.push_back(new Capacitor(id, node1, node2, capacitance));
}

void CircuitBuilder::addInductor(const std::string& id, int n1, int n2, double inductance) {
    Node* node1 = getOrCreateNode(n1);
    Node* node2 = getOrCreateNode(n2);
    edges.push_back(new Inductor(id, node1, node2, inductance));
}

const std::vector<Edge*>& CircuitBuilder::getEdges() const {
    return edges;
}


bool CircuitBuilder::capacitorExists(const std::string& id) const {
    for (const auto& edge : edges) {
        if (edge->getType() == "Capacitor" && edge->getId() == id)
            return true;
    }
    return false;
}

void CircuitBuilder::deleteCapacitor(const std::string& id) {
    auto it = std::remove_if(edges.begin(), edges.end(),
        [&](Edge* edge) {
            if (edge->getType() == "Capacitor" && edge->getId() == id) {
                delete edge;
                return true;
            }
            return false;
        });
    edges.erase(it, edges.end());
}

bool CircuitBuilder::inductorExists(const std::string& id) const {
    for (const auto& edge : edges) {
        if (edge->getType() == "Inductor" && edge->getId() == id)
            return true;
    }
    return false;
}

void CircuitBuilder::deleteInductor(const std::string& id) {
    auto it = std::remove_if(edges.begin(), edges.end(),
        [&](Edge* edge) {
            if (edge->getType() == "Inductor" && edge->getId() == id) {
                delete edge;
                return true;
            }
            return false;
        });
    edges.erase(it, edges.end());
}


bool CircuitBuilder::nodeExists(const std::string& nodeName) const {
    return nodeNameToNumber.find(nodeName) != nodeNameToNumber.end();
}

void CircuitBuilder::createNode(const std::string& nodeName) {
    if (!nodeExists(nodeName)) {
        int nodeNumber = nextNodeNumber++;
        nodeNameToNumber[nodeName] = nodeNumber;
        nodes[nodeNumber] = new Node(nodeNumber);
    }
}

void CircuitBuilder::setGroundNode(const std::string& nodeName) {
    if (nodeExists(nodeName)) {
        groundNode = nodeNameToNumber[nodeName];
    }
}

void CircuitBuilder::deleteGroundNode(const std::string& nodeName) {
    if (nodeExists(nodeName) && groundNode == nodeNameToNumber[nodeName]) {
        groundNode = 0; // Reset to default ground
    }
}

std::vector<std::string> CircuitBuilder::getAllNodeNames() const {
    std::vector<std::string> names;
    for (const auto& pair : nodeNameToNumber) {
        names.push_back(pair.first);
    }
    return names;
}

std::vector<std::string> CircuitBuilder::getComponentList(const std::string& type) const {
    std::vector<std::string> result;
    for (const auto& edge : edges) {
        if (type.empty() || edge->getType() == type) {
            result.push_back(edge->getInfoString()); // Implement getInfoString() in Edge and derived classes
        }
    }
    return result;
}