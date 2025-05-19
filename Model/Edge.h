//
// Created by asus on 5/19/2025.
//

#ifndef EDGE_H
#define EDGE_H



#include <string>

class Edge {
protected:
    std::string type;     // نوع المان (مثلا "Resistor", "Capacitor")
    std::string id;       // شناسه یا نام المان
    int node1;            // شماره گره اول گره مثبت
    int node2;            // شماره گره دوم گره منفی
    double value;         // مقدار المان (مثلا مقاومت، ظرفیت و ...)

public:
    // سازنده (کانستراکتور)
    Edge(const std::string& type, const std::string& id, int node1, int node2, double value);
    virtual ~Edge() = default;

    // Getters
    std::string getType() const;
    std::string getId() const;
    int getNode1() const;
    int getNode2() const;
    double getValue() const;

    // Setters
    void setType(const std::string& type);
    void setId(const std::string& id);
    void setNode1(int node1);
    void setNode2(int node2);
    void setValue(double value);
};



#endif //EDGE_H
