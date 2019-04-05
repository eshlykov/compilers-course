#pragma once

#include <algorithm>

struct Location {
  Location();

  size_t lineNumber_;
  size_t firstColumn_;
  size_t lastColumn_;
};

inline Location::Location() : lineNumber_{1}, firstColumn_{1}, lastColumn_{1} {}
