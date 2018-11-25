#pragma once

#include <algorithm>

class Location {
public:
    Location& operator=(const Location& other);

public:
    int lineNumber_;
    int firstColumn_;
    int lastColumn_;
};
