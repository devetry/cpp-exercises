#include "rational.hpp"

// It's not allowed to declare `class Rational` again,
// since it's already in rational.hpp. Instead, to define
// functions as if they're inside that `class` block,
// use the :: scoping operator. For example, you can
// define `reduceToLowestTerms` like this:
void Rational::reduceToLowestTerms() {

}

uint64_t gcd(uint64_t a, uint64_t b)
{
    // Base cases
    if (a == 0)
    {
        return b;
    }
    if (b == 0)
    {
        return a;
    }

    uint64_t larger = (a >= b) ? a : b;
    uint64_t smaller = larger == a ? b : a;
    return gcd(smaller, larger % smaller);
}