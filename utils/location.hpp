#pragma once

#include <algorithm>

class Location {
public:
    int lineNumber_;
    int firstColumn_;
    int lastColumn_;

public:
    Location& operator=(const Location& other) {
        lineNumber_ = other.lineNumber_;
        firstColumn_ = other.firstColumn_;
        lastColumn_ = other.lastColumn_;
        return *this;
    }
};
