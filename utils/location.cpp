#include "location.hpp"

Location& Location::operator=(const Location& other) {
    lineNumber_ = other.lineNumber_;
    firstColumn_ = other.firstColumn_;
    lastColumn_ = other.lastColumn_;
    return *this;
}
