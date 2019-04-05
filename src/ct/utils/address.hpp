#pragma once

#include <memory>
#include <string>

namespace Ct {

class Address {
 public:
  Address();

  explicit Address(const std::string& name);

  std::string ToString() const;

 private:
  const std::shared_ptr<const int> dummy_;
  const std::string id_;
};

}  // namespace Ct
