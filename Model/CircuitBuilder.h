#ifndef CIRCUITBUILDER_H
#define CIRCUITBUILDER_H

#include <unordered_map>
#include <vector>
#include <string>
#include "Node.h"
#include "Edge.h"
#include "Resistor.h"
#include "VoltageSource.h"
#include "CurrentSource.h"
#include "CircuitMatrix.h"

class CircuitBuilder {
public:
    CircuitBuilder();

    Node* getOrCreateNode(int nodeNumber);

    void addResistor(const std::string& id, int n1, int n2, double value);
    void addVoltageSource(const std::string& id, int n1, int n2, double value);
    void addCurrentSource(const std::string& id, int n1, int n2, double value);

    CircuitMatrix buildMatrix();

    const std::vector<Edge*>& getEdges() const;
    int getVoltageSourceCount() const;

    // In CircuitBuilder.h
    bool resistorExists(const std::string& id) const;
    void deleteResistor(const std::string& id);

private:
    std::unordered_map<int, Node*> nodes;
    std::vector<Edge*> edges;
    int voltageSourceCount;
};

#endif //CIRCUITBUILDER_H