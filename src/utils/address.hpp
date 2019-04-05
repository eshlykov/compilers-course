#pragma once

#include <memory>
#include <string>

class Address {
 public:
  Address();

  explicit Address(std::string name);

  std::string ToString() const;

 private:
  const std::shared_ptr<const int> dummy_;
  const std::string id_;
};

inline Address::Address()
    : dummy_{std::make_shared<const int>(0)},
      id_{std::to_string(reinterpret_cast<unsigned long long>(dummy_.get()))} {}

inline Address::Address(std::string name)
    : dummy_{nullptr}, id_{std::move(name)} {}

inline std::string Address::ToString() const { return id_; }
