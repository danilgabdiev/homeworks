#ifndef STRING_VIEW_H
#define STRING_VIEW_H
#include <cstddef>
#include <iostream>

class StringViewOutOfRange : public std::exception {};

class StringView {
 public:
  StringView() noexcept;
  StringView(const char* other_str);  // NOLINT
  StringView(const char* other_str, size_t other_size);

  const char& operator[](size_t idx) const;
  const char& At(size_t idx) const;
  const char& Front() const;
  const char& Back() const;

  size_t Size() const;
  size_t Length() const;

  bool Empty() const;
  const char* Data() const;

  void Swap(StringView& other_str);

  void RemovePrefix(size_t prefix_size);
  void RemoveSuffix(size_t suffix_size);

  StringView Substr(size_t pos, size_t count);

 private:
  const char* str_ = nullptr;
  size_t size_ = 0;
};

#endif