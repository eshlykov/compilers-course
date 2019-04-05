#include "storage.hpp"

namespace Ct {

Storage::Storage() : id_{counter_} { ++counter_; }

std::string Storage::ToString() const { return std::to_string(id_); }

bool Storage::operator==(const Storage& other) const {
  return id_ == other.id_;
}

int Storage::counter_ = 0;

}  // namespace Ct
