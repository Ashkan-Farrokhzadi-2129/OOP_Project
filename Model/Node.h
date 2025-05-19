// Model/Node.h
#ifndef NODE_H
#define NODE_H

#include <vector>
#include <memory>  // optional if using smart pointers
#include "Edge.h"

class Node {
private:
    int number;
    double potential;
    std::vector<Edge*> connectedEdges;  // raw pointers, or use smart pointers if you prefer

public:
    // Constructor
    Node(int number, double potential = 0.0);

    // Getters
    int getNumber() const;
    double getPotential() const;
    const std::vector<Edge*>& getConnectedEdges() const;

    // Setters
    void setNumber(int number);
    void setPotential(double potential);

    // Manage edges
    void addEdge(Edge* edge);
    void removeEdge(Edge* edge);
};

#endif // NODE_H
