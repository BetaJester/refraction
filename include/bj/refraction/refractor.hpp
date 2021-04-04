// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/refraction
// for details.

#pragma once

#include <map>
#include <memory>
#include <string>

#define BJ_REFRACT_ME(class_name, base_class) \
    static void init_refract(::bj::refractor<base_class> *info) { \
        info->name = #class_name; \
        info->maker = []() -> std::unique_ptr<base_class>{ return std::make_unique<class_name>(); }; \
    } \
    static inline ::bj::refractor<base_class> refractor{init_refract}

#define BJ_REFRACT_VOID(class_name) \
    static void init_refract(::bj::refractor<void> *info) { \
        info->name = #class_name; \
        info->maker = []() -> void*{ return new class_name; }; \
    } \
    static inline ::bj::refractor<void> refractor{init_refract};

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
    } // namespace impl.

    template<typename BaseClass>
    struct refractor {
        
        using make_object_f = std::unique_ptr<BaseClass>(*)();
        using initer_f = void(*)(refractor *);

        std::string name;
        std::uint32_t crc{};
        make_object_f maker{ nullptr };

        refractor(initer_f init) {
            init(this);
            crc = impl::crc32(name);
            mappy().try_emplace(crc, this);
        }

        static std::unique_ptr<BaseClass> make_object(const std::string &name) {
            const auto &map = mappy();
            if (auto it = map.find(impl::crc32(name)); it != map.end()) {
                return it->second->maker();
            } else {
                return {};
            }
        }

        static std::unique_ptr<BaseClass> make_object(const std::uint32_t crc) {
            const auto &map = mappy();
            if (auto it = map.find(crc); it != map.end()) {
                return it->second->maker();
            } else {
                return {};
            }
        }

    private:
        static std::map<std::uint32_t, refractor *> &mappy() {
            static std::map<std::uint32_t, refractor *> map;
            return map;
        }
    };

    template<>
    struct refractor<void> {

        using make_object_f = void *(*)();
        using initer_f = void(*)(refractor *);

        std::string name;
        std::uint32_t crc{};
        make_object_f maker{ nullptr };

        refractor(initer_f init) {
            init(this);
            crc = impl::crc32(name);
            mappy().try_emplace(crc, this);
        }

        static void *make_object(const std::string &name) {
            const auto &map = mappy();
            if (auto it = map.find(impl::crc32(name)); it != map.end()) {
                return it->second->maker();
            } else {
                return nullptr;
            }
        }

        static void *make_object(const std::uint32_t crc) {
            const auto &map = mappy();
            if (auto it = map.find(crc); it != map.end()) {
                return it->second->maker();
            } else {
                return nullptr;
            }
        }

    private:
        static std::map<std::uint32_t, refractor *> &mappy() {
            static std::map<std::uint32_t, refractor *> map;
            return map;
        }
    };

} // namespace bj.