//
// Created by asus on 5/19/2025.
//

#ifndef EDGE_H
#define EDGE_H



#include <string>
// #include "Node.h"   // REMOVE this include from Edge.h
#include "CircuitMatrix.h"

class Node; // With this forward declaration before the class definition


class Edge {
protected:
    std::string type;     // نوع المان (مثلا "Resistor", "Capacitor")
    std::string id;       // شناسه یا نام المان
    Node* node1;            // شماره گره اول گره مثبت
    Node* node2;            // شماره گره دوم گره منفی
    double value;         // مقدار المان (مثلا مقاومت، ظرفیت و ...)

public:
    // سازنده (کانستراکتور)
    Edge(const std::string& type, const std::string& id, Node* node1, Node* node2, double value);
    virtual ~Edge() = default;

    // Getters
    virtual std::string getType() const = 0;  // pure virtual
    std::string getId() const;
    Node* getNode1() const;
    Node* getNode2() const;
    double getValue() const;

    // Setters
    void setType(const std::string& type);
    void setId(const std::string& id);
    void setNode1(Node* node1);
    void setNode2(Node* node2);
    void setValue(double value);

    // Pure virtual stamp function, takes CircuitMatrix reference to modify
    virtual void stamp(CircuitMatrix& matrix) = 0;
    // NEW: Pure virtual for dynamic stamping
    virtual void updateStamps(double dt, CircuitMatrix& matrix,
                            const Eigen::VectorXd& solution) = 0;

    virtual std::string getInfoString() const = 0;
    virtual double getCurrent(const Eigen::VectorXd& state) const = 0;
};



#endif //EDGE_H
