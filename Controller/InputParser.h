#ifndef INPUTPARSER_H
#define INPUTPARSER_H

#include <string>
#include <istream>
#include "CircuitBuilder.h"
#include "InputError.h"

class InputParser {
public:
    InputParser(CircuitBuilder& builder);

    // Parse a single line of input (e.g., "R1 1 2 1000")
    void parseLine(const std::string& line);

    // Parse multiple lines from an input stream (e.g., std::cin or file)
    void parseStream(std::istream& in);

private:
    CircuitBuilder& builder;
};

#endif // INPUTPARSER_H