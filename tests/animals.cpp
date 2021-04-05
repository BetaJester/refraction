// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/refraction
// for details.

#include <catch2/catch.hpp>
#include "animals.hpp"

TEST_CASE("Dogs say woof!", "[animals,dog]") {

    auto jimmy = bj::instantiate<anim::animal>("dog");

    REQUIRE(jimmy);

    REQUIRE(jimmy->talk() == "Woof!");

}

TEST_CASE("Elvy says meow!", "[animals,cat]") {

    auto elvy = bj::instantiate<anim::animal>("cat");

    REQUIRE(elvy);

    REQUIRE(elvy->talk() == "Meow!");

}

TEST_CASE("Failure is an option", "[animals,fail]") {

    auto thing = bj::instantiate<anim::animal>("thing");

    REQUIRE_FALSE(thing);
}