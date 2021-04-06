// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/refraction
// for details.

#pragma once

#include <string_view>
#include <bj/refraction/refractor.hpp>

namespace anim {

    class [[nodiscard]] animal_auto {

    public:

        virtual ~animal_auto() noexcept = default;
        virtual std::string_view talk() const noexcept = 0;

    };

    class [[nodiscard]] dog_auto final : public animal_auto{

        static inline bj::refractor<dog_auto, animal_auto> refractor;

    public:

        std::string_view talk() const noexcept override { return "Woof!"; }

    };

    class [[nodiscard]] cat_auto final : public animal_auto{

        static inline bj::refractor<cat_auto, animal_auto> refractor;

    public:

        std::string_view talk() const noexcept override { return "Meow!"; }

    };

} // namespace anim.