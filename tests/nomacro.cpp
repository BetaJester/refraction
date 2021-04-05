// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/refraction
// for details.

#include <catch2/catch.hpp>
#include <bj/refraction/refractor.hpp>

struct nombase {};

struct nommer : nombase {

    static inline bj::refractor<nommer, nombase> refractor{ "nommer" };

};

struct vnommer {

    static inline bj::refractor<vnommer, void> refractor{ "vnommer" };

};

TEST_CASE("nomacro refractor works", "[nomacro]") {

    auto a = bj::instantiate<nombase>("nommer");
    REQUIRE(a);
    REQUIRE(nommer::refractor.crc() == 0x2feaa36e);

    auto b = bj::instantiate<void>("vnommer");
    REQUIRE(b);
    delete b;

}