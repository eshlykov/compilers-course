#pragma once

#include <string>

class Address {
 public:
  Address() : label_("A" + std::to_string(counter_++)) {}
  explicit Address(std::string label) : label_(std::move(label)) {}

  std::string ToString() const { return label_; }

 private:
  std::string label_;
  static int counter_;
};
