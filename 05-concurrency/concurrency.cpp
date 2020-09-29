#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include <thread>
#include <iostream>
#include <vector>
#include <mutex>

void addValue(int& accum, int i) {
    int temp = accum;
    temp += i;
    accum = temp;
}

int runThreads() {
    int accum = 0;
    std::vector<std::thread> threads;
    for (int i=0; i < 100; i++) {
        // we need to pass the reference of accum to the thread
        // but we can't pass the reference through the thread constructor
        // wrapping accum in std:ref allows us to pass the reference
        threads.push_back(std::thread(addValue, std::ref(accum), i));
    }

    for (auto& th: threads) {
        th.join();
    }
    return accum;
}

TEST_CASE( "We end up with 4950" ) {
    std::vector<int> tests;
    for (int i=0; i< 10; i++) {
        tests.push_back(runThreads());
    }
    REQUIRE( std::all_of(tests.begin(), tests.end(), [](int i){ return i == 4950; }) );

}
