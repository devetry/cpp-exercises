#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "rational.hpp"

TEST_CASE("gcd works as expected", "[gcd]") {
  REQUIRE(gcd(12, 3) == 3);
  REQUIRE(gcd(24, 30) == 6);
  REQUIRE(gcd(1, 4) == 1);
  REQUIRE(gcd(4, 1) == 1);
  REQUIRE(gcd(19, 14) == 1);
}

TEST_CASE("Rationals can be created", "[constructor]") {
  Rational();
  Rational(12);
  Rational(2, 4);
}

TEST_CASE("Rationals can be read into strings", "[toString]") {
  auto r1 = Rational();
  REQUIRE(r1.toString() == "0 / 1");

  auto r2 = Rational(12);
  REQUIRE(r2.toString() == "12 / 1");

  auto r3 = Rational(1, 2);
  REQUIRE(r3.toString() == "1 / 2");
}

TEST_CASE("Rationals are put in lowest terms", "[lowestTerms]") {
  auto r1 = Rational(2, 4);
  REQUIRE(r1.toString() == "1 / 2");

  auto r2 = Rational(12, -3);
  REQUIRE(r2.toString() == "-4 / 1");
}