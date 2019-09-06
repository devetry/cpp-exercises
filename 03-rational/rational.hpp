#ifndef _RATIONAL_H_
#define _RATIONAL_H_
#include <cstdint>
#include <string>

// Euclid's algorithm to calculate the
// greatest common divisor can be looked
// up on wikipedia. It will be used in the
// reduceToLowestTerms function
uint64_t gcd(uint64_t a, uint64_t b);

class Rational {
private:
  int64_t _numerator;
  int64_t _denominator;

  // put in lowest terms. Ensure that
  // 1. If one of _numerator and _denominator is negative, it is the numerator.
  // 2. If both are negative, convert both to positive
  // 3. The numerator and denominator have no common factors. (this is where you use gcd)
  void reduceToLowestTerms(); // I recommend using GCD for this.
public:
  Rational(); // default constructor, produces 0/1
  Rational(int64_t p, int64_t q = 1);

  // produce a string like "{numerator} / {denominator}"
  std::string toString() const;

  //        Using "+" on a Rational
  //               │  and another Rational
  // produces a    │        │
  // │ new Rational│        │
  // ▼             ▼        ▼
  Rational operator+ (const Rational&) const;
  //                     ▲                ▲
  //                     │                │
  //  The other Rational is not modified  │
  //                                      │
  //                 And neither is this one


  Rational operator- (const Rational&) const;
  Rational operator* (const Rational&) const;
  Rational operator/ (const Rational&) const;
  bool operator== (const Rational&) const;
  bool operator!= (const Rational&) const;
  bool operator> (const Rational&) const;
  bool operator>= (const Rational&) const;
  bool operator< (const Rational&) const;
  bool operator<= (const Rational&) const;
};

#endif
