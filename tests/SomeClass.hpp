// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/refraction
// for details.

#pragma once

#include <bj/refraction/refractor.hpp>

namespace honk {

    struct SomeBaseClass {

        BJ_REFRACT_ME(honk::SomeBaseClass, honk::SomeBaseClass);

        virtual ~SomeBaseClass() noexcept = default;
        virtual std::string_view name() const noexcept { return "honk::SomeBaseClass"; }
    };

    struct [[nodiscard]] SomeClass final : public SomeBaseClass {

        BJ_REFRACT_ME(honk::SomeClass, honk::SomeBaseClass);

        int id{};
        char ccc{};

        std::string_view name() const noexcept override { return refractor.name(); }

    };

};