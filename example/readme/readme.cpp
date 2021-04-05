// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/refraction
// for details.

#include <iostream>
#include <string_view>
#include <bj/refraction/refractor.hpp>

struct base {
    virtual ~base() = default;
    virtual std::string_view name() { return "base"; }
};

struct derived : base {
    BJ_REFRACT_ME(derived, base);
    std::string_view name() override { return "derived"; }
};

struct standalone {
    // No base class? Void pointers, good luck.
    BJ_REFRACT_VOID(standalone);
    const int size() { return 42; }
};

int main() {
    // Good place for 'auto', explicit for example.
    std::unique_ptr<base> object = bj::instantiate<base>("derived");
    std::cout << "Object class name: " << object->name() << std::endl;

    // Good place for unique_ptr and a cast one liner, explicit for example again.
    void *sa_void_object = bj::instantiate<void>("standalone");
    standalone *sa_object = reinterpret_cast<standalone *>(sa_void_object);
    std::cout << "Standalone size: " << sa_object->size() << std::endl;
    delete sa_object;
}