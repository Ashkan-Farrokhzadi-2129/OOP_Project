#include "CurrentSource.h"
#include "Node.h"

CurrentSource::CurrentSource(const std::string& id, Node* node1, Node* node2, double current)
    : Edge("CurrentSource", id, node1, node2, current) {}

std::string CurrentSource::getType() const {
    return "CurrentSource";
}


void CurrentSource::stamp(CircuitMatrix& matrix) {
    int n1 = node1->getNumber();
    int n2 = node2->getNumber();
    double curr = value;

    // For current sources, add to J vector (node current injections)
    if (n1 != 0)
        matrix.J(n1 - 1) -= curr;
    if (n2 != 0)
        matrix.J(n2 - 1) += curr;
}

void CurrentSource::updateStamps(double dt, CircuitMatrix& matrix,
                     const Eigen::VectorXd& solution) {
    //Empty
}