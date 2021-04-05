// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/refraction
// for details.

#pragma once

#include <limits>
#include <memory> // unique_ptr
#include <string>
#include <string_view>
#include <concepts>
#include <unordered_map>
#include <utility> // move.
#include <cstdint> // uint32_t

// Implementation details, don't touch.
namespace bj::impl::inline v1 {

    // Adapted from https://stackoverflow.com/a/27950866/8612306 and comments.
    // Gives a non-standard crc32 for a string.
    [[nodiscard]] inline constexpr std::uint32_t crc32(std::string_view str) noexcept {
        std::uint32_t crc = std::numeric_limits<std::uint32_t>::max();
        for (auto c : str) {
            crc ^= static_cast<unsigned char>(c);
            for (std::size_t k{}; k < 8; ++k) {
                crc = (crc >> 1) ^ (0x82F63B78 & (0 - (crc & 1)));
            }
        }
        return crc;
    }

    // Wrapper for information about a refractor type.
    template<typename Base>
    struct make_return {
        
        // The return type for Base as a pointer type.
        using type = std::unique_ptr<Base>;

        // Returns a pointer type of the base class, for a new object of the derived class.
        template<std::derived_from<Base> Derived>
        [[nodiscard]] static type make() { return std::make_unique<Derived>(); }
    };

    // Specialization of the make_return type with no base class.
    template<>
    struct make_return<void> {
        
        // The return type for a class with no base type.
        using type = void *;

        // Returns a new object of a type, returned as a pointer with no type.
        template<typename Class> [[nodiscard]] static type make() { return new Class; }
    };

    // Stores information related to a refractor with a base type.
    template<typename Base>
    struct refractor_info {
        using return_info = make_return<Base>;
        using make_object_f = typename return_info::type(*)();
        std::uint32_t crc{};
        std::string name;
        make_object_f maker{ nullptr };
    };

    // A map of refractor into to crc "hashes". Due to C++ statics and templates,
    // there is one produced per base class used.
    template<typename Base>
    struct map {

        // The enclosed map type, may change.
        using map_t = std::unordered_map<std::uint32_t, const refractor_info<Base> *>;

        // Magic static for the enclosed map type.
        [[nodiscard]] static map_t &get() {
            static map_t map;
            return map;
        }
    };

} // namespace bj::impl.


namespace bj::inline v1 {

    // The return type of a refractor using a certain base.
    template<typename Base>
    using refract_return_t = typename impl::refractor_info<Base>::return_info::type;
    
    // Makes a pointer type of a base type to a new object of a derived type.
    template<typename Derived, typename Base> requires std::derived_from<Derived, Base> || std::is_void_v<Base>
    [[nodiscard]] refract_return_t<Base> refract_make() {
        return impl::refractor_info<Base>::return_info::template make<Derived>();
    }

    // Instantiate a refracted object from the list of types registered for a base type
    // using a registered crc "hash".
    template<typename Base>
    [[nodiscard]] refract_return_t<Base> instantiate(const std::uint32_t crc) {
        const auto &map = impl::map<Base>::get();
        if (auto it = map.find(crc); it != map.end()) {
            return it->second->maker();
        } else {
            return {};
        }
    }

    // Instantiate a refracted object from the list of types registered for a base type
    // using a registered name string.
    template<typename Base>
    [[nodiscard]] refract_return_t<Base> instantiate(const std::string_view name) {
        return instantiate<Base>(impl::crc32(name));
    }

    // Stores and builds information relating to a type into a list of types
    // registered for a specific base, or void.
    template<typename Derived, typename Base>
    struct [[nodiscard]] refractor {
        refractor(std::string name) {
            info.crc = impl::crc32(name);
            info.name = std::move(name);
            info.maker = []() -> refract_return_t<Base> { return refract_make<Derived, Base>(); };
            impl::map<Base>::get().emplace(info.crc, &info);
        }

        [[nodiscard]] const std::string& name() const noexcept { return info.name; }
        [[nodiscard]] std::uint32_t crc() const noexcept { return info.crc; }

        refractor(const refractor &) = delete;
        refractor(refractor &&) = delete;
        refractor& operator=(const refractor &) = delete;
        refractor& operator=(refractor &&) = delete;

    private:

        impl::refractor_info<Base> info;
    };

} // namespace bj.

// Stores and builds information relating to a type into a list of types
// registered for a specific base.
#define BJ_REFRACT_ME(Derived, Base) static inline ::bj::refractor<Derived, Base> refractor { #Derived }

// Stores and builds information relating to a type into a list of types
// registered for void.
#define BJ_REFRACT_VOID(Class) static inline ::bj::refractor<Class, void> refractor { #Class }
