## Concurrency

In this exercise we want to look at an important concept in programming: Concurrency. We will specifically be looking at how threading in C++ works and how to protect critical sections of code.

In Multithreading, a process contains 1 or more threads that share memory between the main process and all the threads. The addition of threads can help speed up processing across an infinite range of problems. Let's take a look at an example program:

```cpp
#include <thread>
#include <string>
#include <iostream>


void function_1(){
    for (int i=0; i > -20; i--) {
        std::cout << "From t1: " << i << std::endl;
    }

}


int main() {
    std::thread t1(function_1);

    for (int i=0; i<20; i++) {
        std::cout << "From main: " << i << std::endl;
    }
    t1.join();

    return 0;
}
```

This program creates one thread that runs function_1 and waits for the thread to finish. What would you expect the output to be? You can copy this code into a cpp file and compile and run it with the command `g++ -std=c++11 <file>.cpp` and then run the example `./a.out` 

We would expect it to print everything cout statement in a separate line, but that is not always the case. Why is this? When writing to the console, or any stream, content is first written to a buffer. Which is then flushed and written to the console. A race condition can happen in this code where before a statement can be flushed to the terminal, the other thread adds their message to the buffer. Resulting in what looks like nonsense.

As we can see, we have a _critical section_ of code where we make an assumption the buffer won't change before we output to the terminal. How do we synchronize this code to ensure output is written out correctly? C++ has mutexes to solve this problem. We can solve this by protecting our write functions.

```cpp
#include <thread>
#include <string>
#include <iostream>
#include <mutex>

std::mutex mu;

void shared_print(std::string msg, int id) {
 mu.lock();
 std::cout << msg << id << std::endl;
 mu.unlock();

}

void function_1(){
    for (int i=0; i > -20; i--) {
        shared_print(string("From t1: "), i);
    }

}


int main() {
    std::thread t1(function_1);

    for (int i=0; i<20; i++) {
        shared_print(string("From Main: "), i);
    }
    t1.join();

    return 0;
}
```
The above would solve our problem and we will get nice output. But it isn't complete. What if we raise an exception in that protected block? We would never release the lock and no other threads could move forward.

The standard library has something called a `lock_guard` which is a mutex wrapper that uses __RAII__: Resource Acquisition is Instantiation. Which means that to be able to succeed initializing the object it must acquire the resource, the lock in this case. When we leave the scope of the function, we automatically give up the lock as it is tied to the lifetime of the `lock_guard` object.

```cpp
mutex mu; //declared outside the function
void shared_print(std::string msg, int id) {
 std::lock_guard<std::mutex> lock(mu);
 std::cout << msg << id << std::endl;
}
```

Now if we were to except while writing out to the terminal we would still release the lock!

## Try it yourself
Can you get the test passing in `concurrency.cpp`? Let's start off by compiling the program with `make build` and running it: `./concurrency`.
