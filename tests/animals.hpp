// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/refraction
// for details.

#pragma once

#include <string_view>
#include <bj/refraction/refractor.hpp>

namespace anim {

    class [[nodiscard]] animal {

    public:

        virtual ~animal() noexcept = default;
        virtual std::string_view talk() const noexcept = 0;

    };

    class [[nodiscard]] dog final : public animal {

        BJ_REFRACT_ME(dog, animal);

    public:

        std::string_view talk() const noexcept override { return "Woof!"; }

    };

    class [[nodiscard]] cat final : public animal {

        BJ_REFRACT_ME(cat, animal);

    public:

        std::string_view talk() const noexcept override { return "Meow!"; }

    };

} // namespace anim.