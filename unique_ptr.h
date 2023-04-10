#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H
#include <iostream>

template <class T>
class UniquePtr {
 public:
  T* Get() const {
    return ptr_;
  }

  UniquePtr() : ptr_(nullptr) {
  }

  explicit UniquePtr(T* other) : ptr_(other) {
  }

  UniquePtr(const UniquePtr<T>& other) = delete;
  UniquePtr& operator=(const UniquePtr<T>& other) = delete;

  UniquePtr(UniquePtr&& other) noexcept {
    ptr_ = other.ptr_;
    other.ptr_ = nullptr;
  }

  T* Release() {
    T* copy = ptr_;
    ptr_ = nullptr;
    return copy;
  }

  void Swap(UniquePtr& other) {
    UniquePtr temp = std::move(other);
    other = std::move(*this);
    *this = std::move(temp);
  }

  void Reset(T* ptr = nullptr) {
    delete ptr_;
    ptr_ = ptr;
  }

  UniquePtr& operator=(UniquePtr&& other) noexcept {
    Reset(other.ptr_);
    other.ptr_ = nullptr;
    return *this;
  }

  T& operator*() const {
    return *Get();
  }

  T* operator->() const {
    return Get();
  }

  explicit operator bool() const {
    return (Get() != nullptr);
  }

  ~UniquePtr() {
    delete ptr_;
  }

 private:
  T* ptr_;
};

#endif