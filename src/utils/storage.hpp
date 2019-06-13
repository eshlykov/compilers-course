#pragma once

#include <string>

class Storage {
 public:
  Storage() : name_("S" + std::to_string(counter_++)) {}
  explicit Storage(std::string name) : name_(std::move(name)) {}

  std::string ToString() { return name_; }

 private:
  std::string name_;
  static int counter_;
};
