//
// Created by asus on 5/19/2025.
//

#include "Edge.h"


// Constructor
Edge::Edge(const std::string& type, const std::string& id, Node* node1, Node* node2, double value)
    : type(type), id(id), node1(node1), node2(node2), value(value) {}

// Getters
std::string Edge::getType() const {
    return type;
}

std::string Edge::getId() const {
    return id;
}

Node* Edge::getNode1() const {
    return node1;
}

Node* Edge::getNode2() const {
    return node2;
}

double Edge::getValue() const {
    return value;
}

// Setters
void Edge::setType(const std::string& type) {
    this->type = type;
}

void Edge::setId(const std::string& id) {
    this->id = id;
}

void Edge::setNode1(Node* node1) {
    this->node1 = node1;
}

void Edge::setNode2(Node* node2) {
    this->node2 = node2;
}

void Edge::setValue(double value) {
    this->value = value;
}