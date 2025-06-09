#include "Capacitor.h"
#include "CircuitMatrix.h"
#include "Node.h"
#include <cmath>

Capacitor::Capacitor(const std::string& id, Node* node1, Node* node2, double capacitance)
    : Edge("Capacitor", id, node1, node2, capacitance) {}

std::string Capacitor::getType() const {
    return "Capacitor";
}

void Capacitor::stamp(CircuitMatrix& matrix) {
    // DC stamp: open circuit (no stamping)
}


void Capacitor::updateStamps(double dt, CircuitMatrix& matrix, const Eigen::VectorXd& voltages) {
    int n1 = node1->getNumber() - 1; // assuming nodes are 1-based
    int n2 = node2->getNumber() - 1;

    // Companion model: G_eq = 2C/dt, I_eq = - (2C/dt)*V_prev - I_prev
    double G_eq = (2.0 * value) / dt;
    double I_eq = -G_eq * prevVoltage - prevCurrent;

    // Stamp the conductance
    if (n1 >= 0) matrix.G(n1, n1) += G_eq;
    if (n2 >= 0) matrix.G(n2, n2) += G_eq;
    if (n1 >= 0 && n2 >= 0) {
        matrix.G(n1, n2) -= G_eq;
        matrix.G(n2, n1) -= G_eq;
    }

    // Stamp the current source
    if (n1 >= 0) matrix.J(n1) -= I_eq;
    if (n2 >= 0) matrix.J(n2) += I_eq;

    // Update previous values for next time step
    double currentVoltage = (n1 >= 0 ? voltages(n1) : 0) - (n2 >= 0 ? voltages(n2) : 0);
    prevCurrent = G_eq * currentVoltage + I_eq;
    prevVoltage = currentVoltage;
}

std::string Capacitor::getInfoString() const {
    return id + " " +
           std::to_string(node1->getNumber()) + " " +
           std::to_string(node2->getNumber()) + " " +
           std::to_string(value);
}