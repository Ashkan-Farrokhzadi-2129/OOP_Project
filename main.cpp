#include <iostream>
#include <string>
#include "InputParser.h"
#include "InputError.h"
#include "CircuitBuilder.h"

int main() {
    CircuitBuilder builder;
    InputParser parser(builder);
    std::string line;

    std::cout << "Enter circuit commands (type 'exit' to quit):\n";
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, line);
        if (line == "exit") break;

        try {
            parser.parseLine(line);
        } catch (const InputError& e) {
            std::cout << e.what() << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Unhandled error: " << e.what() << std::endl;
        }
    }
    return 0;
}