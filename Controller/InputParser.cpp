#include "InputParser.h"
#include <regex>
#include <sstream>
#include <iostream>
#include <cctype>
#include "InputError.h"

InputParser::InputParser(CircuitBuilder& builder) : builder(builder) {}

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

        // 1. Check element name starts with uppercase 'R'
        if (id.empty() || id[0] != 'R') {
            throw InputError("Error: Element " + id + " not found in library");
        }

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

        // 2. Check for duplicate resistor name
        // You need to implement this method in CircuitBuilder:
        // bool resistorExists(const std::string& id) const;
        if (builder.resistorExists(id)) {
            throw InputError("Error: Resistor " + id + " already exists in the circuit");
        }

        // Convert node names to numbers (e.g., N001 -> 1, GND -> 0)
        // int n1 = (node1 == "GND") ? 0 : std::stoi(node1.substr(1));
        // int n2 = (node2 == "GND") ? 0 : std::stoi(node2.substr(1));

        builder.addResistor(id, node1, node2, value);
        return;
    }
    if (std::regex_match(line, match, deleteResistorPattern)) {
        std::string id = match[1];

        // 3. Check for resistor existence before deleting
        // You need to implement this method in CircuitBuilder:
        // bool resistorExists(const std::string& id) const;
        if (!builder.resistorExists(id)) {
            throw InputError("Error: Cannot delete resistor; component not found");
        }

        // Implement deletion logic in CircuitBuilder if needed
        builder.deleteResistor(id);
        return;
    }

    static const std::regex addCapacitorPattern(
        R"(^\s*add\s+(C\w*)\s+(\w+)\s+(\w+)\s+([-+]?\d*\.?\d+(?:[eE][-+]?\d+)?[uUnNμfF]*)\s*$)"
    );
    static const std::regex deleteCapacitorPattern(
        R"(^\s*delete\s+(C\w*)\s*$)"
    );

    // Add Capacitor
    if (std::regex_match(line, match, addCapacitorPattern)) {
        std::string id = match[1];
        std::string node1 = match[2];
        std::string node2 = match[3];
        std::string valueStr = match[4];

        // 1. Check element name starts with uppercase 'C'
        if (id.empty() || id[0] != 'C') {
            throw InputError("Error: Element " + id + " not found in library");
        }

        // Parse value and unit
        double value = 0.0;
        std::string numPart, unitPart;
        size_t i = 0;
        while (i < valueStr.size() && (std::isdigit(valueStr[i]) || valueStr[i] == '.' || valueStr[i] == '-' || valueStr[i] == '+' || valueStr[i] == 'e' || valueStr[i] == 'E')) {
            numPart += valueStr[i++];
        }
        unitPart = valueStr.substr(i);

        try {
            value = std::stod(numPart);
        } catch (...) {
            throw InputError("Error: Syntax error");
        }

        // Unit conversion
        if (unitPart == "u" || unitPart == "U" || unitPart == "μ" || unitPart == "uf" || unitPart == "uF" || unitPart == "μF" || unitPart == "Uf" || unitPart == "UF")
            value *= 1e-6;
        else if (unitPart == "n" || unitPart == "N" || unitPart == "nf" || unitPart == "nF" || unitPart == "Nf" || unitPart == "NF")
            value *= 1e-9;
        else if (unitPart == "f" || unitPart == "F" || unitPart == "") // Farad or no unit
            value *= 1.0;

        if (value <= 0) {
            throw InputError("Error: Capacitance cannot be zero or negative");
        }

        // 2. Check for duplicate capacitor name
        if (builder.capacitorExists(id)) {
            throw InputError("Error: Capacitor " + id + " already exists in the circuit");
        }

        // Convert node names to numbers (e.g., N001 -> 1, GND -> 0)
        // int n1 = (node1 == "GND") ? 0 : std::stoi(node1.substr(1));
        // int n2 = (node2 == "GND") ? 0 : std::stoi(node2.substr(1));

        builder.addCapacitor(id, node1, node2, value);
        return;
    }

    // Delete Capacitor
    if (std::regex_match(line, match, deleteCapacitorPattern)) {
        std::string id = match[1];

        if (!builder.capacitorExists(id)) {
            throw InputError("Error: Cannot delete capacitor; component not found");
        }

        builder.deleteCapacitor(id);
        return;
    }

    static const std::regex addInductorPattern(
        R"(^\s*add\s+(L\w*)\s+(\w+)\s+(\w+)\s+([-+]?\d*\.?\d+(?:[eE][-+]?\d+)?[mMuUμhH]*)\s*$)"
    );
    static const std::regex deleteInductorPattern(
        R"(^\s*delete\s+(L\w*)\s*$)"
    );

    // Add Inductor
    if (std::regex_match(line, match, addInductorPattern)) {
        std::string id = match[1];
        std::string node1 = match[2];
        std::string node2 = match[3];
        std::string valueStr = match[4];

        // 1. Check element name starts with uppercase 'L'
        if (id.empty() || id[0] != 'L') {
            throw InputError("Error: Element " + id + " not found in library");
        }

        // Parse value and unit
        double value = 0.0;
        std::string numPart, unitPart;
        size_t i = 0;
        while (i < valueStr.size() && (std::isdigit(valueStr[i]) || valueStr[i] == '.' || valueStr[i] == '-' || valueStr[i] == '+' || valueStr[i] == 'e' || valueStr[i] == 'E')) {
            numPart += valueStr[i++];
        }
        unitPart = valueStr.substr(i);

        try {
            value = std::stod(numPart);
        } catch (...) {
            throw InputError("Error: Syntax error");
        }

        // Unit conversion
        if (unitPart == "m" || unitPart == "M" || unitPart == "mh" || unitPart == "mH" || unitPart == "Mh" || unitPart == "MH")
            value *= 1e-3;
        else if (unitPart == "u" || unitPart == "U" || unitPart == "μ" || unitPart == "uh" || unitPart == "uH" || unitPart == "μH" || unitPart == "Uh" || unitPart == "UH")
            value *= 1e-6;
        else if (unitPart == "h" || unitPart == "H" || unitPart == "") // Henry or no unit
            value *= 1.0;

        if (value <= 0) {
            throw InputError("Error: Inductance cannot be zero or negative");
        }

        // 2. Check for duplicate inductor name
        if (builder.inductorExists(id)) {
            throw InputError("Error: inductor " + id + " already exists in the circuit");
        }

        // Convert node names to numbers (e.g., N001 -> 1, GND -> 0)
        // int n1 = (node1 == "GND") ? 0 : std::stoi(node1.substr(1));
        // int n2 = (node2 == "GND") ? 0 : std::stoi(node2.substr(1));

        builder.addInductor(id, node1, node2, value);
        return;
    }

    // Delete Inductor
    if (std::regex_match(line, match, deleteInductorPattern)) {
        std::string id = match[1];

        if (!builder.inductorExists(id)) {
            throw InputError("Error: Cannot delete inductor; component not found");
        }

        builder.deleteInductor(id);
        return;
    }

    static const std::regex addGroundPattern(
        R"(^\s*add\s+GND\s+(\w+)\s*$)"
    );
    static const std::regex deleteGroundPattern(
        R"(^\s*delete\s+GND\s+(\w+)\s*$)"
    );

    // Add Ground
    if (std::regex_match(line, match, addGroundPattern)) {
        std::string nodeName = match[1];

        // Check element name is exactly "GND"
        if (line.substr(4, 3) != "GND") {
            throw InputError("Error: Element GND not found in library");
        }

        // Create node if it doesn't exist
        if (!builder.nodeExists(nodeName)) {
            builder.createNode(nodeName); // You need to implement this if not present
        }
        builder.setGroundNode(nodeName); // You need to implement this
        return;
    }

    // Delete Ground
    if (std::regex_match(line, match, deleteGroundPattern)) {
        std::string nodeName = match[1];

        if (!builder.nodeExists(nodeName)) {
            std::cout << "Node does not exist" << std::endl;
            return;
        }
        builder.deleteGroundNode(nodeName); // You need to implement this
        return;
    }

    static const std::regex showNodesPattern(R"(^\s*\.nodes\s*$)");
    static const std::regex listPattern(R"(^\s*\.list\s*(\w*)\s*$)");

    // Show all nodes
    if (std::regex_match(line, match, showNodesPattern)) {
        std::cout << "Available nodes:\n";
        auto nodeNames = builder.getAllNodeNames(); // You need to implement this
        bool first = true;
        for (const auto& name : nodeNames) {
            if (!first) std::cout << ", ";
            std::cout << name;
            first = false;
        }
        std::cout << std::endl;
        return;
    }

    // List all components or by type
    if (std::regex_match(line, match, listPattern)) {
        std::string type = match[1];
        auto components = builder.getComponentList(type); // You need to implement this
        for (const auto& comp : components) {
            std::cout << comp << std::endl;
        }
        return;
    }

    static const std::regex tranPattern(
    R"(^\s*\.TRAN\s+([\d\.eE+-]+)\s+([\d\.eE+-]+)\s*$)"
    );

    if (std::regex_match(line, match, tranPattern)) {
    double tStep = std::stod(match[1]);
    double tStop = std::stod(match[2]);

    if (tStep <= 0 || tStop <= 0) {
        throw InputError("Error: Invalid .TRAN parameters");
    }

    // Call your transient analysis function (implement this in your controller/model)
    builder.runTransientAnalysis(tStep, tStop);
    return;
    }

    static const std::regex printTranPattern(
    R"(^\s*\.print\s+TRAN\s+([\d\.eE+-]+)\s+([\d\.eE+-]+)(?:\s+[\d\.eE+-]+)?(?:\s+[\d\.eE+-]+)?((?:\s+[VI]\([^)]+\))+)\s*$)"
    );

    if (std::regex_match(line, match, printTranPattern)) {
    double tStep = std::stod(match[1]);
    double tStop = std::stod(match[2]);
    std::string varsStr = match[3];

    // Extract variables (e.g., V(n001), I(R1), ...)
    std::vector<std::string> variables;
    std::regex varRegex(R"(([VI]\([^)]+\)))");
    auto varsBegin = std::sregex_iterator(varsStr.begin(), varsStr.end(), varRegex);
    auto varsEnd = std::sregex_iterator();
    for (auto it = varsBegin; it != varsEnd; ++it) {
        variables.push_back(it->str());
    }

        // Error handling for missing nodes/components
    for (const auto& var : variables) {
        if (var[0] == 'V') {
            // Voltage: V(node)
            std::string nodeName = var.substr(2, var.size() - 3);
            if (!builder.nodeExists(nodeName)) {
                throw InputError("Node " + nodeName + " not found in circuit");
            }
        } else if (var[0] == 'I') {
            // Current: I(component)
            std::string compName = var.substr(2, var.size() - 3);
            if (!builder.componentExists(compName)) {
                throw InputError("Component " + compName + " not found in circuit");
            }
        }
    }

    builder.runTransientPrint(tStep, tStop, variables);
    return;
    }

    static const std::regex addVoltageSourcePattern(
    R"(^\s*add\s+VoltageSource(\w+)\s+(\w+)\s+(\w+)\s+([-+]?\d*\.?\d+(?:[eE][-+]?\d+)?)\s*$)"
    );
    static const std::regex addCurrentSourcePattern(
    R"(^\s*add\s+CurrentSource(\w+)\s+(\w+)\s+(\w+)\s+([-+]?\d*\.?\d+(?:[eE][-+]?\d+)?)\s*$)"
    );

    // Add Voltage Source
if (std::regex_match(line, match, addVoltageSourcePattern)) {
    std::string id = match[1].str(); // Prefix with 'V' for consistency
    std::string node1 = match[2];
    std::string node2 = match[3];
    double value = std::stod(match[4]);

    if (builder.componentExists(id)) {
        throw InputError("Error: Voltage source " + id + " already exists in the circuit");
    }

    // int n1 = (node1 == "GND") ? 0 : std::stoi(node1.substr(1));
    // int n2 = (node2 == "GND") ? 0 : std::stoi(node2.substr(1));
    builder.addVoltageSource(id, node1, node2, value);
    return;
}

// Add Current Source
if (std::regex_match(line, match, addCurrentSourcePattern)) {
    std::string id = match[1].str(); // Prefix with 'I' for consistency
    std::string node1 = match[2];
    std::string node2 = match[3];
    double value = std::stod(match[4]);

    if (builder.componentExists(id)) {
        throw InputError("Error: Current source " + id + " already exists in the circuit");
    }

    // int n1 = (node1 == "GND") ? 0 : std::stoi(node1.substr(1));
    // int n2 = (node2 == "GND") ? 0 : std::stoi(node2.substr(1));
    builder.addCurrentSource(id, node1, node2, value);
    return;
}

    throw InputError("Error: Syntax error");
}