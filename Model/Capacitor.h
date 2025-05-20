#ifndef CAPACITOR_H
#define CAPACITOR_H

#include "Edge.h"
#include <string>

class Capacitor : public Edge {
public:
    Capacitor(const std::string& id, Node* node1, Node* node2, double capacitance);

    std::string getType() const override;
};

#endif // CAPACITOR_H
