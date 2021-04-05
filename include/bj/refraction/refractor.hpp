// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/refraction
// for details.

#pragma once

#include <unordered_map>
#include <memory>
#include <string>

namespace bj {

    namespace impl {

        [[nodiscard]] inline constexpr std::uint32_t crc32(const std::string_view str) noexcept {
            std::uint32_t crc = std::numeric_limits<std::uint32_t>::max();
            for (auto c : str) {
                crc ^= static_cast<unsigned char>(c);
                for (std::size_t k{}; k < 8; ++k) {
                    crc = (crc >> 1) ^ (0x82F63B78 & (0 - (crc & 1)));
                }
            }
            return crc;
        }

        template<typename T> struct make_return {
            using type = std::unique_ptr<T>;
            template<typename C> static type make() { return std::make_unique<C>(); }
        };

        template<> struct make_return<void> {
            using type = void*;
            template<typename C> static type make() { return new C; }
        };

        template<typename Base>
        struct refractor_info {
            using return_info = make_return<Base>;
            using make_object_f = typename return_info::type(*)();
            std::uint32_t crc{};
            std::string name;
            make_object_f maker{ nullptr };
        };

        template<typename Base>
        struct map {
            using map_t = std::unordered_map<std::uint32_t, refractor_info<Base>*>;
            static map_t &get() {
                static map_t map;
                return map;
            }
        };

    } // namespace impl.

    template<typename Base> using refract_return_t = typename impl::refractor_info<Base>::return_info::type;
    template<typename Child, typename Base> refract_return_t<Base> refract_make() {
        return impl::refractor_info<Base>::return_info::template make<Child>();
    }

    template<typename Base>
    refract_return_t<Base> instantiate(const std::string_view name) {
        const auto &map = impl::map<Base>::get();
        if (auto it = map.find(impl::crc32(name)); it != map.end()) {
            return it->second->maker();
        } else {
            return {};
        }
    }

    template<typename Base>
    refract_return_t<Base> instantiate(const std::uint32_t crc) {
        const auto &map = impl::map<Base>::get();
        if (auto it = map.find(crc); it != map.end()) {
            return it->second->maker();
        } else {
            return {};
        }
    }

    template<typename Child, typename Base>
    struct refractor {
        refractor(std::string name) {
            info.crc = impl::crc32(name);
            info.name = std::move(name);
            info.maker = []() -> refract_return_t<Base> { return refract_make<Child, Base>(); };
            impl::map<Base>::get().emplace(info.crc, &info);
        }
        impl::refractor_info<Base> info;
    };

#define BJ_REFRACT_ME(Child, Base) static inline ::bj::refractor<Child, Base> refractor { #Child }
#define BJ_REFRACT_VOID(Child) static inline ::bj::refractor<Child, void> refractor { #Child }

} // namespace bj.