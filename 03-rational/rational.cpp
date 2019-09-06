#include "rational.hpp"
#include <sstream>

uint64_t gcd(uint64_t a, uint64_t b) {
  while (b != 0) {
    uint64_t temp = b;
    b = a % b;
    a = temp;
  }
  return a;
}


void Rational::reduceToLowestTerms() {
  auto oneNegative = _numerator < 0 ^ _denominator < 0;
  _numerator = abs(_numerator);
  _denominator = abs(_denominator);
  auto d = gcd(_numerator, _denominator);
  _numerator /= d;
  _denominator /= d;
  if (oneNegative) {
    _numerator *= -1;
  }
}
Rational::Rational (): _numerator{0}, _denominator{1} {}
Rational::Rational (int64_t p, int64_t q): _numerator{p}, _denominator{q} {
  reduceToLowestTerms();
}

std::string Rational::toString() const {
  std::ostringstream os;
  os << _numerator << " / " << _denominator;
  return os.str();
}