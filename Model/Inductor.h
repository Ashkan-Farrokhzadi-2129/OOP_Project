#ifndef INDUCTOR_H
#define INDUCTOR_H

#include "Edge.h"
#include <string>

class Inductor : public Edge {
public:
    Inductor(const std::string& id, Node* node1, Node* node2, double inductance);

    std::string getType() const override;
};

#endif // INDUCTOR_H
