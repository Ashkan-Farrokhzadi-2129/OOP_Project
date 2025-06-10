#include "CircuitBuilder.h"
#include "TimeSolver.h"
#include <iostream>

CircuitBuilder::CircuitBuilder() : voltageSourceCount(0) {}

Node* CircuitBuilder::getOrCreateNode(const std::string& nodeName) {
    createNode(nodeName); // will do nothing if already exists
    int nodeNumber = nodeNameToNumber[nodeName];
    return nodes[nodeNumber];
}

void CircuitBuilder::addResistor(const std::string& id, const std::string& n1, const std::string& n2, double value) {
    Node* node1 = getOrCreateNode(n1);
    Node* node2 = getOrCreateNode(n2);
    edges.push_back(new Resistor(id, node1, node2, value));
}

void CircuitBuilder::addVoltageSource(const std::string& id, const std::string& n1, const std::string& n2, double value) {
    Node* node1 = getOrCreateNode(n1);
    Node* node2 = getOrCreateNode(n2);
    edges.push_back(new VoltageSource(id, node1, node2, value, voltageSourceCount));
    voltageSourceCount++;
}

void CircuitBuilder::addCurrentSource(const std::string& id, const std::string& n1, const std::string& n2, double value) {
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

void CircuitBuilder::addCapacitor(const std::string& id, const std::string& n1, const std::string& n2, double capacitance) {
    Node* node1 = getOrCreateNode(n1);
    Node* node2 = getOrCreateNode(n2);
    edges.push_back(new Capacitor(id, node1, node2, capacitance));
}

void CircuitBuilder::addInductor(const std::string& id, const std::string& n1, const std::string& n2, double inductance) {
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
        nodeNumberToName[nodeNumber] = nodeName; // <-- Add this line
        nodes[nodeNumber] = new Node(nodeNumber);
    }
}

void CircuitBuilder::setGroundNode(const std::string& nodeName) {
    if (!nodeExists(nodeName)) return;
    // Only allow one ground node (besides default 0)
    if (groundNode != 0 && groundNode != nodeNameToNumber[nodeName]) {
        std::cout << "Error: Multiple ground nodes are not allowed" << std::endl;
        return;
    }
    groundNode = nodeNameToNumber[nodeName];
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

void CircuitBuilder::runTransientAnalysis(double tStep, double tStop) {
    LinearEquationSolver solver;
    CircuitMatrix matrix(static_cast<int>(nodes.size()), voltageSourceCount);

    matrix.assemble(edges);

    Eigen::VectorXd state = Eigen::VectorXd::Zero(nodes.size() + voltageSourceCount);

    for (double t = 0; t <= tStop; t += tStep) {
        // Update dynamic components (capacitors, inductors, etc.)
        matrix.updateDynamicComponents(tStep, state, edges);

        // Solve for the next state
        state = matrix.solve(solver);

        // Output voltages/currents as needed
        std::cout << "t=" << t << ": ";
        for (int i = 0; i < nodes.size(); ++i)
            std::cout << "V(" << i+1 << ")=" << state(i) << " ";
        std::cout << std::endl;
    }
}

void CircuitBuilder::runTransientPrint(double tStep, double tStop, const std::vector<std::string>& variables) {
    LinearEquationSolver solver;
    CircuitMatrix matrix(static_cast<int>(nodes.size()), voltageSourceCount);
    matrix.assemble(edges);
    Eigen::VectorXd state = Eigen::VectorXd::Zero(nodes.size() + voltageSourceCount);

    // Print header
    std::cout << "t";
    for (const auto& var : variables) std::cout << "\t" << var;
    std::cout << std::endl;

    for (double t = 0; t <= tStop; t += tStep) {
        matrix.updateDynamicComponents(tStep, state, edges);
        state = matrix.solve(solver);

        // Update capacitor histories after solving
        for (auto* edge : edges) {
            if (auto* cap = dynamic_cast<Capacitor*>(edge)) {
                cap->updateHistory(state.head(nodes.size()));
            }
        }

        std::cout << t;
        for (const auto& var : variables) {
            if (var[0] == 'V') {
            std::string nodeName = var.substr(2, var.size() - 3);
            int nodeNum = nodeNameToNumber.count(nodeName) ? nodeNameToNumber.at(nodeName) : -1;
                if (nodeNum == 0) {
                    std::cout << "\t0"; // Ground node is always 0V
                } else if (nodeNum > 0 && nodeNum - 1 < state.size()) {
                    std::cout << "\t" << state(nodeNum - 1);
                } else {
                    std::cout << "\tNaN";
                }
            }
            else if (var[0] == 'I') {
                // Current: I(element)
                std::string elemId = var.substr(2, var.size() - 3);
                double current = 0.0;
                bool found = false;
                for (const auto& edge : edges) {
                    if (edge->getId() == elemId) {
                        current = edge->getCurrent(state);
                        found = true;
                        break;
                    }
                }
                std::cout << "\t" << (found ? current : NAN);
            }
        }
        std::cout << std::endl;
    }
}

bool CircuitBuilder::componentExists(const std::string& id) const {
    for (const auto& edge : edges) {
        if (edge->getId() == id) {
            return true;
        }
    }
    return false;
}


bool CircuitBuilder::renameNode(const std::string& oldName, const std::string& newName) {
    if (!nodeExists(oldName) || nodeExists(newName)) return false;

    int nodeNum = nodeNameToNumber[oldName];
    nodeNameToNumber.erase(oldName);
    nodeNameToNumber[newName] = nodeNum;
    nodeNumberToName[nodeNum] = newName;

    // Update all edges that reference this node
    for (auto* edge : edges) {
        if (edge->getNode1()->getName() == oldName)
            edge->getNode1()->setName(newName);
        if (edge->getNode2()->getName() == oldName)
            edge->getNode2()->setName(newName);
    }
    return true;
}