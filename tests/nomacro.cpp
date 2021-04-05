// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/refraction
// for details.

#include <catch2/catch.hpp>
#include <bj/refraction/refractor.hpp>

struct base {};

struct derived : base {
    static inline bj::refractor<derived, base> refractor{ "derived" };
};

struct standalone {
    static inline bj::refractor<standalone, void> refractor{ "standalone" };
};

TEST_CASE("nomacro refractor works", "[nomacro]") {

    auto a = bj::instantiate<base>("derived");
    REQUIRE(a);
    REQUIRE(derived::refractor.crc() == 0x8590e4c);

    auto b = bj::instantiate<void>("standalone");
    REQUIRE(b);
    delete reinterpret_cast<standalone*>(b);

}