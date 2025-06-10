#include "VoltageSource.h"
#include "CircuitMatrix.h"
#include "Node.h"

VoltageSource::VoltageSource(const std::string& id, Node* node1, Node* node2, double voltage, int matrixIndex)
    : Edge("VoltageSource", id, node1, node2, voltage), matrixIndex(matrixIndex) {}

std::string VoltageSource::getType() const {
    return "VoltageSource";
}

void VoltageSource::stamp(CircuitMatrix& matrix) {
    int pos = node1->getNumber();
    int neg = node2->getNumber();
    int vsIdx = getMatrixIndex();

    if (pos != 0) {
        matrix.B(pos - 1, vsIdx) = 1;
        matrix.C(vsIdx, pos - 1) = 1;
    }
    if (neg != 0) {
        matrix.B(neg - 1, vsIdx) = -1;
        matrix.C(vsIdx, neg - 1) = -1;
    }
    matrix.E(vsIdx) = value;
}

int VoltageSource::getMatrixIndex() const {
    return matrixIndex;
}

void VoltageSource::updateStamps(double dt, CircuitMatrix& matrix,
                     const Eigen::VectorXd& solution) {
    //Empty
}


std::string VoltageSource::getInfoString() const {
    return id + " " +
           std::to_string(node1->getNumber()) + " " +
           std::to_string(node2->getNumber()) + " " +
           std::to_string(value);
}

double VoltageSource::getCurrent(const Eigen::VectorXd& state) const {
    // The current through the voltage source is stored at its matrix index in the solution vector
    int idx = getMatrixIndex();
    if (idx >= 0 && idx < state.size()) {
        return state(idx);
    } else {
        return 0.0;
    }
}