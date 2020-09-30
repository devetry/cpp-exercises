## 02 - Swap

In this module we will be working on passing by reference, function overloading, and function templates. C++ differs from javascript in the fact a value being passed to a function can be by value (we make a copy of the parameter) or by reference (we pass the location in memory where the paramter is located). The advantage to passing by reference is you avoid having to copy large objects when they are needed which can lead to speed up in your code.

Lets take an example:
I have a function that takes an integer and adds one to it

```C++
void addOne(int ref) {
    ref = ref + 1;
}

int main() {
    int i = 10;
    addOne(i);
}
```

Would 'i' be changed in the main function? 

It would not. The above function passes by value, so everytime that function is called, a copy of the parameter is made and passed to the function. In the above example only inside `addOne` is 'i' changed to 11;

To pass by reference we need to add an ampersand on to the type of the parameter. In this next example 'i' in the `main` function would be changed to 11 after being called by `addOne`.

```C++
void addOne(int& ref) { //passing by reference
    ref = ref + 1;
}
int main() {
    int i = 10;
    addOne(i);
}
```

Let's say now we want to be able to add one to a float, for this to work we would need to overload `addOne` so there is a function signature that takes a float.

```C++
void addOne(int& ref) { 
    ref = ref + 1;
}
void addOne(float& ref) { 
    ref = ref + 1;
}
int main() {
    int i = 10;
    addOne(i);
    float f = 10.0f;
    addOne(f);

}
```
The compiler can read this code and correctly use the function for the specific type. But what if we want to create an addOne function for a double, or an unsigned int? Does this mean we potentially have to write 100 addOne functions?

C++ has __function templates__. We can create a generic template that can define the logic used and then generate functions for the types we want. This allows us to define the logic of a function regardless of the type. In the case above we could rewrite the logic into a generic function. 

```C++
template <typename T>
void addOne(T& ref) { 
    ref = ref + 1;
}

int main() {
    int i = 10;
    addOne(i); // the compiler can implicity figure out what function it needs to generate
    float f = 10.0f;
    addOne<float>(f); // Or we can be explicit

}

```
There are two test files in this directory. One to create overloaded functions and another to create a generic. Try and get them to pass

## Check your work

Run the first example by running the command `make build-swap` and then running `./swap`.

Run the second example by running `make build-genswap` and then running `./genswap`

