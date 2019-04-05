#pragma once

#include <string>

namespace Irt {

class Storage {
 public:
  Storage();

  std::string ToString() const;

  bool operator==(const Storage& other) const;

 private:
  static int counter_;
  int id_;
};

}  // namespace Irt
