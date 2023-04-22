#ifndef ARRAY_H
#define ARRAY_H

template <class T, size_t N>
class Array {
 public:
  T arr[N];

  void Fill(const T& value) {
    for (size_t i = 0; i < N; ++i) {
      arr[i] = value;
    }
  }

  void Swap(Array<T, N>& other) {
    for (size_t i = 0; i < N; ++i) {
      std::swap(arr[i], other.arr[i]);
    }
  }

  size_t Size() const noexcept {
    return N;
  }

  bool Empty() const noexcept {
    return N;
  }

  T& At(size_t idx) {
    if ((idx < 0) || (idx >= N)) {
      throw E{};
    }

    return arr[idx];
  }

  const T& At(size_t idx) const {
    if ((idx < 0) || (idx >= N)) {
      throw E{};
    }

    return arr[idx];
  }

  T& Front() {
    return arr[0];
  }

  const T& Front() const { 
    return arr[0];
  }

  T& Back() {
    return arr[N];
  }

  const T& Back() const {
    return arr[N];
  }

  T* Data() {
    return arr;
  }

  const T* Data() const {
    return arr;
  }

  T& operator[](size_t idx) {
    return arr[idx];
  }

  const T& operator[](size_t idx) const {
    return arr[idx];
  }
};

#endif