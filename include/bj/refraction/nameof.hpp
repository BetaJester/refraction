// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/refraction
// for details.

#pragma once

#include <algorithm>
#include <string>
#include <string_view>
#include <version>

namespace bj::inline v1 {

// Sometimes you just have to use macros, they are undefined at the end of the file.
#if defined(_MSC_VER)
    #define FUNCNAME __FUNCSIG__
#else 
    // defined(__clang__) || defined(__GNUC__)
    // assumed, maybe other odd compatible compilers.
    #define FUNCNAME __PRETTY_FUNCTION__
#endif

#if defined(__cpp_lib_constexpr_string)
    #define bjcxstring constexpr
#else
    #define bjcxstring
#endif

    namespace impl {

        // Helper for detection of pretty function lengths.
        class AAAdetectBBB {};

        // Completely remove substrings from a string.
        inline bjcxstring void remove_substr(std::string &str, std::string_view substr) noexcept
        {
            std::string::size_type start{};
            while (start != std::string::npos) {
                start = str.find(substr);
                if (start != std::string::npos) {
                    str.erase(start, size(substr));
                }
            }
        }

        // Replace substrings in a string.
        inline bjcxstring void replace_substr(std::string &str, std::string_view subold, std::string_view subnew) noexcept
        {
            std::string::size_type start{};
            while (start != std::string::npos) {
                start = str.find(subold);
                if (start != std::string::npos) {
                    str.replace(start, size(subold), subnew);
                }
            }
        }

    } // namespace bj::inline v1::impl.

    // Automatically get the positions from the start and end of the compiler
    // string for a functions retty name to get the correct name.
    // namesz() must have the same signiature length as nameof() for this to work.
    template<typename T = impl::AAAdetectBBB>
    [[nodiscard]] inline constexpr auto namesz() noexcept
    {
        std::string_view name{FUNCNAME};

        auto start = name.find("class bj::v1::impl::AAA");
        if (start == std::string_view::npos) {
            start = name.find("bj::v1::impl::AAA");
        }
        auto finish = name.find("BBB") + 3;
        auto end = name.size() - finish;

        return std::pair{ start, end };
    }

    // Get the compiler specific string naming a type. Results can vary by
    // compiler and standard library implementations.
    template<typename T>
    [[nodiscard]] inline constexpr auto nameof() noexcept
    {
        std::string_view name{FUNCNAME};
        const auto bounds = namesz();
        std::string_view::iterator a = name.begin() + bounds.first;
        std::string_view::iterator b = name.end() - bounds.second;
        return std::string_view(a, b);
    }

    // Get the string for a type name, cleaned of compiler specific oddities where
    // they are identified.
    template<typename T>
    [[nodiscard]] inline bjcxstring std::string clean_nameof() noexcept
    {
        std::string name{ nameof<T>() };
        impl::remove_substr(name, "struct ");
        impl::remove_substr(name, "class ");
        impl::remove_substr(name, "enum ");
        impl::replace_substr(name, "long int", "long");
        name.erase(std::remove(begin(name), end(name), ' '), end(name));
        return name;
    }

// Clean house.
#undef FUNCNAME
#undef bjcxstring

} // namespace bj::inline v1.