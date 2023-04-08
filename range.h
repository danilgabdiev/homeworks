#ifndef RANGE_H
#define RANGE_H
#define Begin begin
#define End end
#include <iostream>

class Range {
 private:
  int begin_ = 0;
  int end_ = 0;
  int size_ = 0;
  int step_ = 1;

 public:
  class Iterator {
   private:
    int it_;
    int step_ = 1;

   public:
    explicit Iterator(int ptr, int step);
    Iterator(const Iterator& other);

    Iterator& operator++();
    Iterator operator++(int);
    Iterator& operator=(const Iterator& other);

    Iterator& operator+=(int n);

    int operator->() const;

    int operator*() const;

    bool operator==(const Iterator& other) const;

    bool operator!=(const Iterator& other) const;
  };

  Iterator Begin() const;

  Iterator End() const;

  explicit Range(int end);

  explicit Range(int begin, int end);

  Range(int begin, int end, int step);
};

#endif