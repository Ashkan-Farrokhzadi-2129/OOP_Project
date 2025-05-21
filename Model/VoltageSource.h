#ifndef VOLTAGESOURCE_H
#define VOLTAGESOURCE_H

#include "Edge.h"
#include <string>

class VoltageSource : public Edge {
public:
    VoltageSource(const std::string& id, Node* node1, Node* node2, double voltage, int matrixIndex);

    std::string getType() const override;
    int getMatrixIndex() const;

    void stamp(CircuitMatrix& matrix) override;

private:
    int matrixIndex; // Index of this voltage source in the MNA matrix
};


#endif // VOLTAGESOURCE_H
