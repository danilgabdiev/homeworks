#include <iostream>
#include "range.h"
#define Begin begin
#define End end

Range::Iterator::Iterator(int ptr, int step) : it_(ptr), step_(step) {
}

Range::Iterator::Iterator(const Iterator& other) {
  it_ = other.it_;
}

Range::Iterator& Range::Iterator::operator++() {
  it_ += step_;
  return *this;
}

Range::Iterator Range::Iterator::operator++(int) {
  Iterator copy = *this;
  it_++;
  return copy;
}

Range::Iterator& Range::Iterator::operator=(const Iterator& other) = default;

Range::Iterator& Range::Iterator::operator+=(int n) {
  it_ = it_ + n;
  return *this;
}

int Range::Iterator::operator->() const {
  return it_;
}

int Range::Iterator::operator*() const {
  return it_;
}

bool Range::Iterator::operator==(const Iterator& other) const {
  return (it_ == other.it_);
}

bool Range::Iterator::operator!=(const Iterator& other) const {
  return !(it_ == other.it_);
}

Range::Iterator Range::Begin() const {
  return Iterator(begin_, step_);
}

Range::Iterator Range::End() const {
  return Iterator(end_, step_);
}

Range::Range(int end) {
  if (end > 0) {

    begin_ = 0;
    end_ = end;
  }
}

Range::Range(int begin, int end) {
  if (begin < end) {
    begin_ = begin;
    end_ = end;
  }
}

Range::Range(int begin, int end, int step) {
  if (((begin < end) && (step > 0)) || ((begin > end) && (step < 0))) {
    begin_ = begin;
    end_ = end;
    step_ = step;
  }
}