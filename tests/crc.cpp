// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/refraction
// for details.

#include <catch2/catch.hpp>
#include <bj/refraction/refractor.hpp>

struct crctester {

    BJ_REFRACT_ME(crctester, crctester);

    int x{ 203 };
};

TEST_CASE("crc refractor works", "[crc]") {

    auto a = bj::instantiate<crctester>("crctester");
    REQUIRE(a);

    const auto crc = crctester::refractor.info.crc;
    auto b = bj::instantiate<crctester>(crc);
    REQUIRE(b);

}