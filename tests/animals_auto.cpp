// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/refraction
// for details.

#include <catch2/catch.hpp>
#include "animals_auto.hpp"

TEST_CASE("Dogs say woof (auto)!", "[animals,dog,auto]") {

    auto jimmy = bj::instantiate<anim::animal_auto>("anim::dog_auto");

    REQUIRE(jimmy);

    REQUIRE(jimmy->talk() == "Woof!");

}

TEST_CASE("Elvy says meow (auto)!", "[animals,cat,auto]") {

    auto elvy = bj::instantiate<anim::animal_auto>("anim::cat_auto");

    REQUIRE(elvy);

    REQUIRE(elvy->talk() == "Meow!");

}

TEST_CASE("Failure is an option (auto)", "[animals,fail,auto]") {

    auto thing = bj::instantiate<anim::animal_auto>("thing");

    REQUIRE_FALSE(thing);
}