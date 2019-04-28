#pragma once

#include <string>

class Storage {
 public:
  explicit Storage(bool isFramePointer = false,
                   bool isReturnStorage = false) noexcept;

  std::string ToString() const;

  bool operator==(const Storage& other) const;

  bool IsFramePointer() const;
  bool IsReturnStorage() const;

 private:
  static int counter_;
  const bool isFramePointer_;
  const bool isReturnStorage_;
  int id_;
};

inline Storage::Storage(bool isFramePointer, bool isReturnStorage) noexcept
    : isFramePointer_{isFramePointer},
      id_{counter_},
      isReturnStorage_(isReturnStorage) {
  ++counter_;
}

inline std::string Storage::ToString() const { return std::to_string(id_); }

inline bool Storage::operator==(const Storage& other) const {
  return id_ == other.id_;
}

inline bool Storage::IsFramePointer() const { return isFramePointer_; }

inline bool Storage::IsReturnStorage() const { return isReturnStorage_; }