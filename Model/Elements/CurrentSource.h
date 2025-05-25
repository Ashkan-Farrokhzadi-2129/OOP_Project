#ifndef CURRENTSOURCE_H
#define CURRENTSOURCE_H

#include "Edge.h"
#include <string>

class CurrentSource : public Edge {
public:
    CurrentSource(const std::string& id, Node* node1, Node* node2, double current);

    std::string getType() const override;

    void stamp(CircuitMatrix& matrix) override;
};

#endif // CURRENTSOURCE_H
