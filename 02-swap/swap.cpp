#define CATCH_CONFIG_MAIN
#include <string>
#include "../catch.hpp"

// your functions go here
void ourSwap(std::string& str1, std::string& str2)
{
    std::string tmp = str1;
    str1 = str2;
    str2 = tmp;
}

void ourSwap(int& int1, int& int2)
{
    int tmp = int1;
    int1 = int2;
    int2 = tmp;
}


TEST_CASE( "We can swap strings" ) {
    const std::string STR1 = "I'm string one!";
    const std::string STR2 = "I'm string two!";

    std::string s1 = STR1;
    std::string s2 = STR2;
    ourSwap(s1, s2);
    REQUIRE( s1 == STR2 );
    REQUIRE( s2 == STR1 );
}

TEST_CASE( "We can swap ints" ) {
    const int INT1 = 5;
    const int INT2 = 10;

    // These are ints right? what is this "type"?
    // since C++11 there is an 'auto' keyword that you can use to make the compiler
    // figure out what the type should be. i1 and i2 will become ints
    auto i1 = INT1;
    auto i2 = INT2;
    ourSwap(i1, i2);
    REQUIRE( i1 == INT2 );
    REQUIRE( i2 == INT1 );
}
