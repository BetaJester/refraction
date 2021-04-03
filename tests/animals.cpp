// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/refraction
// for details.

#include <catch2/catch.hpp>
#include "animals.hpp"

TEST_CASE("Dogs say woof!", "[animals,dog]") {

    auto jimmy = bj::refractor<anim::animal>::make_object("dog");

    REQUIRE(jimmy);

    REQUIRE(jimmy->talk() == "Woof!");

}

TEST_CASE("Elvy says meow!", "[animals,cat]") {

    auto elvy = bj::refractor<anim::animal>::make_object("cat");

    REQUIRE(elvy);

    REQUIRE(elvy->talk() == "Meow!");

}

TEST_CASE("Failure is an option", "[animals,fail]") {

    auto thing = bj::refractor<anim::animal>::make_object("thing");

    REQUIRE_FALSE(thing);
}