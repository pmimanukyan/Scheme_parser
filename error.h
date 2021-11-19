#pragma once

#include <stdexcept>

struct SyntaxError : public std::runtime_error {
    SyntaxError() : std::runtime_error("Syntax error") {};
    using std::runtime_error::runtime_error;
};
