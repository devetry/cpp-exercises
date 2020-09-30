#define CATCH_CONFIG_MAIN
#include <string>
#include "../catch.hpp"

// your functions go here



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

    auto i1 = INT1;
    auto i2 = INT2;
    ourSwap(i1, i2);
    REQUIRE( i1 == INT2 );
    REQUIRE( i2 == INT1 );
}

TEST_CASE( "We can swap floats" ) {
    const float FLOAT1 = 33.333; 
    const float FLOAT2 = 12.1234; 

    auto f1 = FLOAT1;
    auto f2 = FLOAT2;
    ourSwap(f1, f2);
    REQUIRE( f1 == FLOAT2 );
    REQUIRE( f2 == FLOAT1 );
}

TEST_CASE( "We can swap doubles" ) {
    const double DOUBLE1 = 5.5;
    const double DOUBLE2 = 10.5;

    auto d1 = DOUBLE1;
    auto d2 = DOUBLE2;
    ourSwap(d1, d2);
    REQUIRE( d1 == DOUBLE2 );
    REQUIRE( d2 == DOUBLE1 );
}
