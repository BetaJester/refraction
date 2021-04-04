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

    template<typename BaseClass>
    struct refractor {
        
        using make_object_f = std::unique_ptr<BaseClass>(*)();
        using initer_f = void(*)(refractor *);

        std::string name;
        make_object_f maker{ nullptr };

        refractor(initer_f init) {
            init(this);
            mappy().try_emplace(name, this);
        }

        static std::unique_ptr<BaseClass> make_object(const std::string &name) {
            const auto &map = mappy();
            if (auto it = map.find(name); it != map.end()) {
                return it->second->maker();
            } else {
                return {};
            }
        }

    private:
        static std::map<std::string, refractor *> &mappy() {
            static std::map<std::string, refractor *> map;
            return map;
        }
    };

    template<>
    struct refractor<void> {

        using make_object_f = void*(*)();
        using initer_f = void(*)(refractor *);

        std::string name;
        make_object_f maker{ nullptr };

        refractor(initer_f init) {
            init(this);
            mappy().try_emplace(name, this);
        }

        static void* make_object(const std::string &name) {
            const auto &map = mappy();
            if (auto it = map.find(name); it != map.end()) {
                return it->second->maker();
            } else {
                return nullptr;
            }
        }

    private:
        static std::map<std::string, refractor *> &mappy() {
            static std::map<std::string, refractor *> map;
            return map;
        }
    };


} // namespace bj.