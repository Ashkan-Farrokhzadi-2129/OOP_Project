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
#include "Capacitor.h"
#include "Inductor.h"
#include "CircuitMatrix.h"

class CircuitBuilder {
public:
    CircuitBuilder();

    Node* getOrCreateNode(const std::string& nodeName);

    void addResistor(const std::string& id, const std::string& n1, const std::string& n2, double value);
    void addVoltageSource(const std::string& id, const std::string& n1, const std::string& n2, double value);
    void addCurrentSource(const std::string& id, const std::string& n1, const std::string& n2, double value);
    void setGroundNode(int nodeNumber);
    void addCapacitor(const std::string& id, const std::string& n1, const std::string& n2, double capacitance);
    void addInductor(const std::string& id, const std::string& n1, const std::string& n2, double inductance);

    CircuitMatrix buildMatrix();

    const std::vector<Edge*>& getEdges() const;
    bool componentExists(const std::string& id) const;
    int getVoltageSourceCount() const;

    // In CircuitBuilder.h
    bool resistorExists(const std::string& id) const;
    void deleteResistor(const std::string& id);

    bool capacitorExists(const std::string& id) const;
    void deleteCapacitor(const std::string& id);

    bool inductorExists(const std::string& id) const;
    void deleteInductor(const std::string& id);

    bool nodeExists(const std::string& nodeName) const;
    void createNode(const std::string& nodeName);
    void setGroundNode(const std::string& nodeName);
    void deleteGroundNode(const std::string& nodeName);

    std::vector<std::string> getAllNodeNames() const;
    std::vector<std::string> getComponentList(const std::string& type = "") const;

    void runTransientAnalysis(double tStep, double tStop);
    void runTransientPrint(double tStep, double tStop, const std::vector<std::string>& variables);


    bool renameNode(const std::string& oldName, const std::string& newName);

private:
    std::unordered_map<std::string, int> nodeNameToNumber; // NEW: maps node name to number
    std::unordered_map<int, std::string> nodeNumberToName; // number -> name
    std::unordered_map<int, Node*> nodes;
    std::vector<Edge*> edges;
    int voltageSourceCount;
    int groundNode = 0; // Default to node 0 as ground
    int nextNodeNumber = 1; // NEW: for assigning unique numbers
};

#endif //CIRCUITBUILDER_H