#include "Inductor.h"
#include "CircuitMatrix.h"
#include <cmath>
#include "Node.h"

Inductor::Inductor(const std::string& id, Node* node1, Node* node2, double inductance)
    : Edge("Inductor", id, node1, node2, inductance) {}

std::string Inductor::getType() const {
    return "Inductor";
}


void Inductor::stamp(CircuitMatrix& matrix) {
    // DC stamp: short circuit (needs special handling)
    // For simplicity, we'll just add a small conductance
    const double smallG = 1e-12;
    int n1 = node1->getNumber() - 1;
    int n2 = node2->getNumber() - 1;

    if (n1 >= 0) matrix.G(n1, n1) += smallG;
    if (n2 >= 0) matrix.G(n2, n2) += smallG;
    if (n1 >= 0 && n2 >= 0) {
        matrix.G(n1, n2) -= smallG;
        matrix.G(n2, n1) -= smallG;
    }
}


void Inductor::updateStamps(double dt, CircuitMatrix& matrix, const Eigen::VectorXd& currents) {
    int n1 = node1->getNumber() - 1;
    int n2 = node2->getNumber() - 1;
    int vsIndex = matrix.getM(); // Assuming we add new voltage sources at the end
    lastCurrentIndex = vsIndex;

    // Companion model: R_eq = 2L/dt, V_eq = (2L/dt)*I_prev + V_prev
    double R_eq = (2.0 * value) / dt;
    double V_eq = R_eq * prevCurrent + prevVoltage;

    // Stamp as a voltage source with series resistance
    if (n1 >= 0) {
        matrix.B(n1, vsIndex) += 1;
        matrix.C(vsIndex, n1) += 1;
    }
    if (n2 >= 0) {
        matrix.B(n2, vsIndex) -= 1;
        matrix.C(vsIndex, n2) -= 1;
    }
    matrix.D(vsIndex, vsIndex) -= R_eq;
    matrix.E(vsIndex) = V_eq;

    // Update previous values for next time step
    prevVoltage = (n1 >= 0 ? currents(n1) : 0) - (n2 >= 0 ? currents(n2) : 0);
    prevCurrent = (V_eq - prevVoltage) / R_eq;
}

std::string Inductor::getInfoString() const {
    return id + " " +
           std::to_string(node1->getNumber()) + " " +
           std::to_string(node2->getNumber()) + " " +
           std::to_string(value);
}

double Inductor::getCurrent(const Eigen::VectorXd& state) const {
    // Use the stored index from the last stamping
    if (lastCurrentIndex >= 0 && lastCurrentIndex < state.size()) {
        return state(lastCurrentIndex);
    } else {
        return 0.0; // Or throw an error if you prefer
    }
}