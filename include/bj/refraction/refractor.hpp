// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/refraction
// for details.

#pragma once

#include <map>
#include <memory>

#define BJ_REFRACT_ME(class_name, base_class) \
    static void init_refract(::bj::refract_info<base_class> *info) { \
        info->name = #class_name; \
        info->maker = []() -> std::unique_ptr<base_class>{ return std::make_unique<class_name>(); }; \
    } \
    static inline ::bj::refract_info<base_class> refract_info{init_refract};

namespace bj {

    template<typename BaseClass>
    struct refract_info {
        
        using make_object_f = std::unique_ptr<BaseClass>(*)();
        using initer_f = void(*)(refract_info *);

        std::string name;
        make_object_f maker{ nullptr };

        refract_info(initer_f init) {
            init(this);
            map[name] = this;
        }

        static std::unique_ptr<BaseClass> make_object(const std::string &name) {
            if (auto it = map.find(name); it != map.end()) {
                return map[name]->maker();
            } else {
                return {};
            }
        }

    private:
        static inline std::map<std::string, refract_info *> map;
    };


} // namespace bj.
