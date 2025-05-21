#include "InputParser.h"
#include <regex>
#include <sstream>
#include <iostream>
#include <cctype>
#include "InputError.h"

InputParser::InputParser(CircuitBuilder& builder)
    : builder(builder) {}

void InputParser::parseLine(const std::string& line) {
    static const std::regex addResistorPattern(
        R"(^\s*add\s+(R\w*)\s+(\w+)\s+(\w+)\s+([-+]?\d*\.?\d+(?:[eE][-+]?\d+)?[kKmM]?)\s*$)"
    );
    static const std::regex deleteResistorPattern(
        R"(^\s*delete\s+(R\w*)\s*$)"
    );

    std::smatch match;
    if (std::regex_match(line, match, addResistorPattern)) {
        std::string id = match[1];
        std::string node1 = match[2];
        std::string node2 = match[3];
        std::string valueStr = match[4];

        // Convert value with unit
        double value = 0.0;
        char unit = std::tolower(valueStr.back());
        if (unit == 'k' || unit == 'm') {
            value = std::stod(valueStr.substr(0, valueStr.size() - 1));
            if (unit == 'k') value *= 1e3;
            else if (unit == 'm') value *= 1e6;
        } else {
            value = std::stod(valueStr);
        }

        if (value <= 0) {
            throw InputError("Error: Resistance cannot be zero or negative");
        }

        // You may want to check for duplicate resistor names here using CircuitBuilder

        // Convert node names to numbers (e.g., N001 -> 1, GND -> 0)
        int n1 = (node1 == "GND") ? 0 : std::stoi(node1.substr(1));
        int n2 = (node2 == "GND") ? 0 : std::stoi(node2.substr(1));

        builder.addResistor(id, n1, n2, value);
        return;
    }
    if (std::regex_match(line, match, deleteResistorPattern)) {
        std::string id = match[1];
        // Implement deletion logic in CircuitBuilder if needed
        // builder.deleteResistor(id);
        return;
    }

    throw InputError("Error: Syntax error");
}