#pragma once

#include <string>

class Storage {
 public:
  Storage() noexcept;

  std::string ToString() const;

  bool operator==(const Storage &other) const;

 private:
  static int counter_;
  int id_;
};

inline Storage::Storage() noexcept : id_{counter_} { ++counter_; }

inline std::string Storage::ToString() const { return std::to_string(id_); }

inline bool Storage::operator==(const Storage &other) const {
  return id_ == other.id_;
}
