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
    int vsIdx = getMatrixIndex(); // You need to provide this index when creating the voltage source

    // B and C matrices
    if (pos >= 0) {
        matrix.B(pos, vsIdx) = 1;
        matrix.C(vsIdx, pos) = 1;
    }
    if (neg >= 0) {
        matrix.B(neg, vsIdx) = -1;
        matrix.C(vsIdx, neg) = -1;
    }

    // E vector
    matrix.E(vsIdx) = value;
}

int VoltageSource::getMatrixIndex() const {
    return matrixIndex;
}