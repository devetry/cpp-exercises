#include <thread>
#include <string>
#include <iostream>
#include <mutex>
#include <unistd.h>

std::mutex mu; // Common MutEx handle


void shared_print(std::string msg, int id)
{
    {
    std::lock_guard<std::mutex> lock(mu); // Lock scoped code
    std::cout << msg << id << std::endl;    
    } // Release lock
    usleep(1);
}

void function_1()
{
    for (int i=0; i > -20; i--)
    {
        shared_print("from t1: ", i);
    }

}


int main()
{
    std::thread t1(function_1);

    for (int i=0; i<20; i++)
    {
        shared_print("From main: ", i);
    }
    t1.join();

    return 0;
}