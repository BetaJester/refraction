// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/refraction
// for details.

#pragma once

#include <algorithm>
#include <string>
#include <string_view>

namespace bj {

    template<typename T>
    std::string gettype() {

#if defined(__clang__)
        std::string name{ __PRETTY_FUNCTION__ + 31, sizeof(__PRETTY_FUNCTION__) - 33 };
#elif defined(__GNUC__)
        std::string name{ __PRETTY_FUNCTION__ + 35, sizeof(__PRETTY_FUNCTION__) - 85 };
#elif defined(_MSC_VER)
        std::string name{ __FUNCSIG__ + 108, sizeof(__FUNCSIG__) - 116 };
#else
#error "Unsupported compiler :("
#endif

        const auto remove_substr = [](std::string &str, std::string_view substr) {
            std::string::size_type start{};
            while (start != std::string::npos) {
                start = str.find(substr);
                if (start != std::string::npos) {
                    str.erase(start, size(substr));
                }
            }
        };

        const auto replace_substr = [](std::string &str, std::string_view subold, std::string_view subnew) {
            std::string::size_type start{};
            while (start != std::string::npos) {
                start = str.find(subold);
                if (start != std::string::npos) {
                    str.replace(start, size(subold), subnew);
                }
            }
        };

        remove_substr(name, "struct ");
        remove_substr(name, "class ");
        remove_substr(name, "enum ");
        replace_substr(name, "long int", "long");

        name.erase(std::remove(begin(name), end(name), ' '), end(name));

        return name;
    }

} // namespace bj.