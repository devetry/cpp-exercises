## Rational Class

In this exercise, we'll make a type to represent rational numbers (fractions). Most of the time, we would represent rational numbers using floats, but this allows inaccuracies to accumulate. Our rational class will not have this problem, because we'll store the numerator and denominator using integers.

Scott Meyer's reminds us that "class design is type design". If a rational number type were included in a programming language, what would we expect it to be able to do?

- Create from a numerator and denominator
- Create just from a numerator and assume the denominator is 1
- Adding two Rational values produces another
- Subtracting two Rational values produces another
- Multiplying two Rational values produces another
- Rationals are always maintained in "lowest terms". So 2/4 would be converted to 1/2. This helps keep our numbers from overflowing.
- Rationals can be compared for equality and order
- and so on...

We'll provide a header, describing what the Rational class should look like. Most of it will be initially commented out, so you don't have to write _all_ the code before running any of it.

We'll also provide test cases to check that your code behaves as expected.

## Instructions

### Warm-up: GCD

Euclid's GCD algorithm is used to find the greatest common divisor of two numbers. For example, if we have 18 and 12, their greatest common divisor is 6. To put 18/12 into lowest terms, we can divide both the numerator and denominator by 6 to get 3/2.

Write a gcd function matching the signature in rational.hpp.

#### Check your work

To check your work, you'll want to comment out the rest of the rational.hpp file (so, everything in that class). Otherwise, the compiler will complain that you didn't provide a definition for the `Rational` class. We just haven't gotten there yet! You'll also need to comment out all but the first `TEST_CASE` in test.cpp, for the same reason.

Now, run `make` to produce an executable called `test`. Run the tests with `./test`. You should get output like this:

```
==============================================
All tests passed (5 assertions in 1 test case)
```

### Constructor time