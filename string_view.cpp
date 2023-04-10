#include <iostream>
#include "string_view.h"

StringView::StringView() noexcept : str_(nullptr), size_(0) {
}

StringView::StringView(const char* other_str) : str_(other_str) {  // NOLINT
  size_t other_size = 0;
  while (other_str[other_size] != '\0') {
    ++other_size;
  }

  size_ = other_size;
}

StringView::StringView(const char* other_str, size_t other_size) : str_(other_str), size_(other_size) {
}

const char& StringView::operator[](size_t idx) const {
  return str_[idx];
}

const char& StringView::At(size_t idx) const {
  if (idx >= size_) {
    throw StringViewOutOfRange{};
  }

  return str_[idx];
}

const char& StringView::Front() const {
  return str_[0];
}

const char& StringView::Back() const {
  return str_[size_ - 1];
}

size_t StringView::Size() const {
  return size_;
}

size_t StringView::Length() const {
  return size_;
}

bool StringView::Empty() const {
  return (size_ == 0);
}

const char* StringView::Data() const {
  return str_;
}

void StringView::Swap(StringView& other_str) {
  std::swap(*this, other_str);
}

void StringView::RemovePrefix(size_t prefix_size) {
  str_ += prefix_size;
  size_ -= prefix_size;
}

void StringView::RemoveSuffix(size_t suffix_size) {
  size_ -= suffix_size;
}

StringView StringView::Substr(size_t pos, size_t count = -1) {
  if (pos >= size_) {
    throw StringViewOutOfRange{};
  }

  return StringView(&str_[pos], std::min(count, Size() - pos));
}