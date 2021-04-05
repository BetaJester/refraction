// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/refraction
// for details.

#include <catch2/catch.hpp>
#include "SomeClass.hpp"

TEST_CASE("Basic class creation works", "[basic]") {

    auto x = bj::instantiate<honk::SomeBaseClass>("honk::SomeClass");

    REQUIRE(x->name() == "honk::SomeClass");

}