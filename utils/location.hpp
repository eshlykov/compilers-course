#pragma once

#include <algorithm>

class Location {
public:
    Location& operator=(const Location& other) {
        lineNumber_ = other.lineNumber_;
        firstColumn_ = other.firstColumn_;
        lastColumn_ = other.lastColumn_;
        return *this;
    }

public:
    int lineNumber_;
    int firstColumn_;
    int lastColumn_;
};
