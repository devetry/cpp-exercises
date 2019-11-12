## Rational Class

In this exercise, we'll make a type to represent rational numbers (fractions). Most of the time, we would represent rational numbers using floats, but this allows inaccuracies to accumulate. Our rational class will not have this problem, because we'll store the numerator and denominator using integers.

Scott Meyers reminds us that "class design is type design". If a rational number type were included in a programming language, what would we expect it to be able to do?

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

**Write a gcd function matching the signature in rational.hpp.**

#### Check your work

To check your work, you'll want to comment out the rest of the rational.hpp file (so, everything in that class). Otherwise, the compiler will complain that you didn't provide a definition for the `Rational` class. We just haven't gotten there yet! You'll also need to comment out all but the first `TEST_CASE` in test.cpp, for the same reason.

Now, run `make` to produce an executable called `test`. Run the tests with `./test`. You should get output like this:

```
==============================================
All tests passed (5 assertions in 1 test case)
```

### Constructor time

C++ is willing to make constructors for you (see [C++ rules for automatic member function generation](http://www.enyo.de/fw/notes/cpp-auto-members.html) for details). For `Rational`, we're happy to accept the compiler-generated constructors for

- `Rational::Rational(const Rational&)`: the copy constructor, which builds a new Rational out of an existing one by copying the member data.
- `Rational& Rational::operator=(const Rational&)`: the copy-assignment operator, which replaces all fields on a Rational by copying the member data.

(There are a couple others that have to do with "move semantics". We'll end up with those too, but we won't use them in this exercise)

The C++ would also make us a default constructor that takes no arguments and just initializes all member data to its default values. For `Rational`, this would be equivalent to:

```cpp
Rational::Rational():
  _numerator{0},
  _denominator{0}
 {}
```

That syntax may look a little funky to you. The _body_ of the constructor is actually that empty block on the last line: `{}`. Our constructor logic is pretty simple and just amounts to "set this value to 0 and this other value also to 0". C++ brace initialization gives us a special syntax for this. In some situations, the brace initialization syntax can be a bit faster, so you'll see it pretty often.

In any case, we're not satisfied with the default constructor. It would make a Rational with a value of "0/0", which is not defined. **Make a new parameterless constructor that initializes the denominator to 1 instead of zero.**

We'll also want to make a constructor that takes arguments. **Write a constructor that accepts two arguments, first the numerator and then the denominator.** Because the header provides a default value for the denominator, your function can be called with either one or two arguments.

#### Check your work

Comment out all the tests other than the `[constructor]` block and the `[gcd]` block. In the `rational.hpp` file, uncomment the class definition. As before, run `make` to create the test executable, and then `./test` to run the tests.

### Reduce to lowest terms

In order to eventually compare Rationals, we need to store them in a consistent way. We'll impose the following rules:

- The denominator will always be positive and non-zero. If a `Rational` number is negative, the sign is always in the numerator.
- `Rational`s are stored in "lowest terms". This means they should have no common factors. You can put a Rational into lowest terms by dividing both the numerator and the denominator by `gcd(numerator, denominator)`.

**Write a private method `reduceToLowestTerms()`. Call this method from your two-argument constructor**.

To check our work, we'll need to implement a `toString()` method. You might ask "why can't the tests look at the values of `_numerator` and `_denominator`?". Those data members are marked private, so code outside the class definition will be unable to access them. We could also write `getNumerator()` and `getDenominator()` methods, but I find them distasteful, and don't see much reason for them beyond testing. We may as well test with strings, and the `toString()` method is useful for debugging.

**Write a public `toString()` method that returns a string made up of the numerator, then a space, then a "/", another space, and finally the denominator.** For example: `5 / 12` or `-3 / 4`.

#### Check your work

Uncomment the `[toString]` and `[lowestTerms]` test blocks. Run `make` and `./test` again.

### Adding two Rationals

In order to add two Rationals, we need to give first find a common denominator. The easiest common denominator between `a / b` and `c / d` is `b*d`. So the sum of two fractions is given by this formula

```
a     c     a*d + c*b
—  +  —  =  —————————
b     d       b * d
```

**Implement the `operator+` function using this formula.**

#### Check your work

Uncomment the `[plus]` test block. Run `make` and `./test`.

### Draw the rest of the owl

At this point, you likely have a bit more confidence in writing these methods. Go ahead and implement the rest of the functions declared in "rational.hpp".

