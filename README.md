## topics

Functions
- overloading by type
- pass by reference, reference to const

Classes
- RAII
- destructor (don't throw in a destructor)
- inheritance
- public/private
- Copy constructor, assignment constructor
- move constructor

Templates
- are we gonna write this compare for each type we need?

Std
- forEach, algorithm
- lambdas

Move semantics and rvalue references

Threading and Locking
 - contention over `cout`; use a mutex.
 - unique_pointer, shared_pointer


## exercises

1. Insertion-sort on integers (we provide pseudo-code and function signature)
2. swap routine for strings (doesn't work unless we use references)
3. swap routine for integers
4. templated swap routine
5. make a Rational class ("class design is type design")
  - operator*, operator+, operator-
  - private data for numerator and denominator
  - private methods for reduce (smallest terms)
6. Linked-list of integers
  - destructor
  - pointers and heap data
7. Templated Linked-list
8. Contention over cout. fix it using a mutex
9. make a parent class that reads from a queue, calls `execute` whenever
  it gets a value and enqueues a future for whatever execute returns.
  Make a class that inherits from this parent and counts letters in the sentences read from a queue
