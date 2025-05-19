// Model/Node.cpp
#include "Node.h"
#include <algorithm>  // for std::remove

Node::Node(int number, double potential)
    : number(number), potential(potential)
{
}

int Node::getNumber() const {
    return number;
}

double Node::getPotential() const {
    return potential;
}

const std::vector<Edge*>& Node::getConnectedEdges() const {
    return connectedEdges;
}

void Node::setNumber(int number) {
    this->number = number;
}

void Node::setPotential(double potential) {
    this->potential = potential;
}

void Node::addEdge(Edge* edge) {
    connectedEdges.push_back(edge);
}

void Node::removeEdge(Edge* edge) {
    connectedEdges.erase(std::remove(connectedEdges.begin(), connectedEdges.end(), edge), connectedEdges.end());
}
