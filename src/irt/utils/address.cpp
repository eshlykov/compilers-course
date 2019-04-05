#include "address.hpp"

namespace Irt {

Address::Address()
    : dummy_{std::make_shared<const int>(0)},
      id_{std::to_string(reinterpret_cast<unsigned long long>(dummy_.get()))} {}

Address::Address(const std::string& name) : dummy_{nullptr}, id_{name} {}

std::string Address::ToString() const { return id_; }

}  // namespace Irt
