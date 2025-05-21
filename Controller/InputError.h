#ifndef INPUTERROR_H
#define INPUTERROR_H

#include <stdexcept>
#include <string>

class InputError : public std::runtime_error {
public:
    explicit InputError(const std::string& message)
        : std::runtime_error(message) {}
};

#endif // INPUTERROR_H