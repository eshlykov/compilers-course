#pragma once

#include <algorithm>

struct Location {
  Location();

  int lineNumber_;
  int firstColumn_;
  int lastColumn_;
};

inline Location::Location() : lineNumber_{1}, firstColumn_{1}, lastColumn_{1} {}
