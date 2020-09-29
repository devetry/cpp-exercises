#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "int_list.hpp"

TEST_CASE("an IntList can be created", "[create]") {
  auto il = new IntList;
  REQUIRE(il != nullptr);
  delete il;
}

TEST_CASE("IntList can accept items", "[push_front]") {
  IntList il;
  il.push_front(2);
  il.push_front(4);
  il.push_front(6);
}

TEST_CASE("Inserted items can be found", "[contains]") {
  IntList il;
  REQUIRE(!il.contains(1));
  REQUIRE(!il.contains(0));

  il.push_front(3);
  il.push_front(1);
  REQUIRE(il.contains(1));
  REQUIRE(il.contains(3));
}

TEST_CASE("Inserted items can be removed", "[remove]") {
  IntList il;
  il.push_front(3);
  il.push_front(1);
  il.push_front(2);

  REQUIRE(il.contains(1));
  REQUIRE(il.contains(2));
  REQUIRE(il.contains(3));

  il.remove(1);
  REQUIRE(!il.contains(1));
  REQUIRE(il.contains(2));
  REQUIRE(il.contains(3));

  il.remove(2);
  REQUIRE(!il.contains(2));
  REQUIRE(il.contains(3));


  il.remove(3);
  REQUIRE(!il.contains(3));
}