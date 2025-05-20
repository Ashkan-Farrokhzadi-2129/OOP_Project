#ifndef VOLTAGESOURCE_H
#define VOLTAGESOURCE_H

#include "Edge.h"
#include <string>

class VoltageSource : public Edge {
public:
    VoltageSource(const std::string& id, Node* node1, Node* node2, double voltage);

    std::string getType() const override;
};

#endif // VOLTAGESOURCE_H
