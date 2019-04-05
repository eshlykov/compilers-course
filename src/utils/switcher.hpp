#pragma once

template <typename T>
class Switcher {
 public:
  Switcher(T&, const T&);
  ~Switcher();

  T& operator*();
  T* operator->();

 private:
  T& data_;
  T defaultValue_;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
Switcher<T>::Switcher(T& data, const T& defaultValue)
    : data_{data}, defaultValue_{defaultValue} {}

template <typename T>
Switcher<T>::~Switcher() {
  data_ = defaultValue_;
}

template <typename T>
T& Switcher<T>::operator*() {
  return data_;
}

template <typename T>
T* Switcher<T>::operator->() {
  return &data_;
}
