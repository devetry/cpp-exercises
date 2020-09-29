#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "rational.hpp"

TEST_CASE("gcd works as expected", "[gcd]") {
  REQUIRE(gcd(12, 3) == 3);
  REQUIRE(gcd(24, 30) == 6);
  REQUIRE(gcd(1, 4) == 1);
  REQUIRE(gcd(4, 1) == 1);
  REQUIRE(gcd(19, 14) == 1);
  REQUIRE(gcd(1, 0) == 1);
  REQUIRE(gcd(0, 4) == 4);
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

  auto r3 = Rational(-4, -4);
  REQUIRE(r3.toString() == "1 / 1");
}

TEST_CASE("Rationals are added to create new Rationals", "[plus]") {
  auto r1 = Rational(1, 2) + Rational(1);
  REQUIRE(r1.toString() == "3 / 2");

  auto r2 = Rational(1, 2) + Rational(1, 3);
  REQUIRE(r2.toString() == "5 / 6");
}

TEST_CASE("Rationals are subtracted to create new Rationals", "[minus]") {
  auto r1 = Rational(1, 2) - Rational(1, 3);
  REQUIRE(r1.toString() == "1 / 6");
}

TEST_CASE("Rationals can be multiplied", "[times]") {
  auto r1 = Rational(4, 3) * Rational(5, 2);
  REQUIRE(r1.toString() == "10 / 3");
}

TEST_CASE("Rationals can be divided", "[dividedBy]") {
  auto r1 = Rational(4, 3) / Rational(5, 2);
  REQUIRE(r1.toString() == "8 / 15");
}

TEST_CASE("Rationals can be compared for equality", "[equals]") {
  auto r1 = Rational(2, 5);
  auto r2 = Rational(4, 10);
  REQUIRE(r1 == r2);

  auto r3 = Rational(10, 4);
  REQUIRE(r1 != r3);
}

TEST_CASE("Rationals can be ordered", "[ordering]") {
  auto r1 = Rational(2, 3);
  auto r2 = Rational(3, 4);
  REQUIRE(r1 < r2);
  REQUIRE(r1 <= r2);
  REQUIRE(r2 > r1);
  REQUIRE(r2 >= r1);
  REQUIRE(r1 <= r1);
}