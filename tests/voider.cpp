// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/refraction
// for details.

#include <catch2/catch.hpp>
#include <bj/refraction/refractor.hpp>

struct voider {

    BJ_REFRACT_VOID(voider);

    int x{ 100 };

};

TEST_CASE("void base works", "[void]") {

    auto a = bj::instantiate<void>("voider");
    auto b = reinterpret_cast<voider *>(a);
    
    REQUIRE(a);
    REQUIRE(b);
    REQUIRE(b->x == 100);

    delete b;
}