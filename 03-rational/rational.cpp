#include "rational.hpp"

void Rational::reduceToLowestTerms() {
    if (_denominator < 0)
    {
        _numerator *= -1;
        _denominator *= -1;
    }

    const int64_t _gcd = gcd(std::abs(_numerator), std::abs(_denominator));
    _numerator /= _gcd;
    _denominator /= _gcd;
}

Rational::Rational():
    _numerator{0},
    _denominator{1}
{}

Rational::Rational(int64_t p, int64_t q):
    _numerator{p},
    _denominator{q}
{
    reduceToLowestTerms();
}

std::string Rational::toString() const
{
    return std::to_string(_numerator) + " / " + std::to_string(_denominator);
}

Rational Rational::operator+ (const Rational& other) const
{
    return Rational((this->_numerator * other._denominator) + (other._numerator * this->_denominator), this->_denominator * other._denominator);
}

Rational Rational::operator- (const Rational& other) const
{
    return Rational((this->_numerator * other._denominator) - (other._numerator * this->_denominator), this->_denominator * other._denominator);
}

Rational Rational::operator* (const Rational& other) const
{
    return Rational(this->_numerator * other._numerator , this->_denominator * other._denominator);
}

Rational Rational::operator/ (const Rational& other) const
{
    return Rational(this->_numerator * other._denominator , this->_denominator * other._numerator);
}

bool Rational::operator== (const Rational& other) const
{
    return (*this - other)._numerator == 0;
}

bool Rational::operator!= (const Rational& other) const
{
    return !(*this == other);
}

bool Rational::operator> (const Rational& other) const
{
    return (*this - other)._numerator > 0;
}

bool Rational::operator>= (const Rational& other) const
{
    return (*this - other)._numerator >= 0;
}

bool Rational::operator< (const Rational& other) const
{
    return (*this - other)._numerator < 0;
}

bool Rational::operator<= (const Rational& other) const
{
    return (*this - other)._numerator <= 0;
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