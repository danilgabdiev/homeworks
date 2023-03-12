#include "rational.h"

int GCD(int a, int b) {
  a = abs(a);
  b = abs(b);

  if (b == 0) {
    return a;
  }

  return GCD(b, a % b);
}

void Rational::Reduce() {
  int gcd = GCD(p_, q_);
  p_ /= gcd;
  q_ /= gcd;

  if (q_ < 0) {
    this->p_ = -p_;
    this->q_ = -q_;
  }
}

Rational::Rational(int p, int q) {
  if (q == 0) {
    throw RationalDivisionByZero();
  }

  this->p_ = p;
  this->q_ = q;
  Reduce();
}

Rational::Rational(const Rational& r) {
  p_ = r.p_;
  q_ = r.q_;
}

Rational::Rational(int value) : p_(value), q_(1) {  // NOLINT
}

Rational::Rational() : p_(0), q_(1) {
}

Rational Rational::operator-() const {
  return {-p_, q_};
}

Rational Rational::operator+() const {
  return {p_, q_};
}

Rational& Rational::operator+=(const Rational& other) {
  p_ = p_ * other.q_ + other.p_ * q_;
  q_ = q_ * other.q_;
  Reduce();
  return *this;
}

Rational& Rational::operator-=(const Rational& other) {
  p_ = p_ * other.q_ - other.p_ * q_;
  q_ = q_ * other.q_;
  Reduce();
  return *this;
}

Rational& Rational::operator*=(const Rational& other) {
  p_ = other.p_ * p_;
  q_ = other.q_ * q_;
  Reduce();
  return *this;
}

Rational& Rational::operator/=(const Rational& other) {
  if (other.p_ == 0) {
    throw RationalDivisionByZero();
  }

  p_ = other.q_ * p_;
  q_ = other.p_ * q_;
  Reduce();
  return *this;
}

Rational& Rational::operator++() {
  *this += 1;
  return *this;
}

Rational Rational::operator++(int) {
  Rational copy = *this;
  ++*this;
  return copy;
}

Rational& Rational::operator--() {
  *this -= 1;
  return *this;
}

Rational Rational::operator--(int) {
  Rational copy = *this;
  --*this;
  return copy;
}

int Rational::GetNumerator() const {
  return p_;
}

int Rational::GetDenominator() const {
  return q_;
}

void Rational::SetNumerator(int value) {
  p_ = value;
  Reduce();
}

void Rational::SetDenominator(int value) {

  if (value == 0) {
    throw RationalDivisionByZero();
  }
  q_ = value;
  Reduce();
}

bool operator==(Rational first, Rational other) {
  int p1 = first.GetNumerator();
  int q1 = first.GetDenominator();
  int p2 = other.GetNumerator();
  int q2 = other.GetDenominator();
  return ((p1 == p2) && (q1 == q2));
}

bool operator!=(Rational first, Rational other) {
  return !(first == other);
}

bool operator>(Rational first, Rational other) {
  int p1 = first.GetNumerator();
  int q1 = first.GetDenominator();
  int p2 = other.GetNumerator();
  int q2 = other.GetDenominator();
  return (p1 * q2 > p2 * q1);
}

bool operator>=(Rational first, Rational other) {
  return (first > other || first == other);
}

bool operator<(Rational first, Rational other) {
  return !(first >= other);
}

bool operator<=(Rational first, Rational other) {
  return (first < other || first == other);
}

Rational operator*(const Rational& first, const Rational& other) {
  Rational copy = first;
  copy *= other;
  return copy;
}

Rational operator/(const Rational& first, const Rational& other) {
  Rational copy = first;
  copy /= other;
  return copy;
}

Rational operator+(const Rational& first, const Rational& other) {
  Rational copy = first;
  copy += other;
  return copy;
}

Rational operator-(const Rational& first, const Rational& other) {
  Rational copy = first;
  copy -= other;
  return copy;
}

std::ostream& operator<<(std::ostream& stream, const Rational object) {
  if (object.GetDenominator() == 1) {
    stream << object.GetNumerator();

  } else {
    stream << object.GetNumerator() << "/" << object.GetDenominator();
  }

  return stream;
}

std::istream& operator>>(std::istream& stream, Rational& object) {
  char pq[24]{'\0'};
  bool is_there_slash = false;
  stream >> pq;
  int i = 23;

  while (pq[i] == '\0') {
    --i;
  }

  int p = 0;
  int q = 0;
  int j = 1;

  while (i >= 0) {

    if (pq[i] != '/' && pq[i] != '+' && pq[i] != '-') {
      if (is_there_slash) {
        p += (int(pq[i]) - 48) * j;
        j *= 10;
      } else {
        q += (int(pq[i]) - 48) * j;
        j *= 10;
      }
    } else if (pq[i] == '-') {
      if (is_there_slash) {
        p *= -1;
      } else {
        q *= -1;
      }
    } else if (pq[i] == '/') {
      is_there_slash = true;
      j = 1;
    }

    if ((i == 0) && !is_there_slash) {
      p = q;
      q = 1;
    }

    --i;
  }

  object.SetNumerator(p);
  object.SetDenominator(q);

  return stream;
}