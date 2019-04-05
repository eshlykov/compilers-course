#pragma once

#include <algorithm>

struct Location {
    Location();

    int lineNumber_;
    int firstColumn_;
    int lastColumn_;
};
