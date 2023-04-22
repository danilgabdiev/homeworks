#ifndef RATIONAL_H
#define RATIONAL_H
#include <iostream>

int GCD(int a, int b);

class RationalDivisionByZero : public std::exception {};

class Rational {
 public:
  Rational(int p, int q);
  Rational(const Rational& r);
  Rational(int value);  // NOLINT
  Rational();

  Rational operator-() const;
  Rational operator+() const;

  Rational& operator+=(const Rational& other);
  Rational& operator-=(const Rational& other);
  Rational& operator*=(const Rational& other);
  Rational& operator/=(const Rational& other);

  Rational& operator++();
  Rational operator++(int);
  Rational& operator--();
  Rational operator--(int);

  int GetNumerator() const;
  int GetDenominator() const;
  void SetNumerator(int value);
  void SetDenominator(int value);

 private:
  int p_;
  int q_;

  void Reduce();
};

bool operator==(Rational first, Rational other);
bool operator!=(Rational first, Rational other);
bool operator>(Rational first, Rational other);
bool operator>=(Rational first, Rational other);
bool operator<(Rational first, Rational other);
bool operator<=(Rational first, Rational other);

Rational operator*(const Rational& first, const Rational& other);
Rational operator/(const Rational& first, const Rational& other);
Rational operator+(const Rational& first, const Rational& other);
Rational operator-(const Rational& first, const Rational& other);

std::ostream& operator<<(std::ostream& stream, const Rational object);
std::istream& operator>>(std::istream& stream, Rational& object);

#endif
