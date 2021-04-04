// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/refraction
// for details.

#include <cstdio>
#include <bj/refraction/refractor.hpp>

struct base {
    virtual ~base() = default;
    virtual const char *name() { return "base"; }
};

struct sub : base {
    BJ_REFRACT_ME(sub, base);
    const char *name() override { return "sub"; }
};

struct standalone {
    // No base class? Void pointers, good luck.
    BJ_REFRACT_VOID(standalone);
    const int size() { return 42; }
};

int main() {
    // Good place for 'auto', explicit for example.
    std::unique_ptr<base> object = bj::refractor<base>::make_object("sub");
    std::puts(object->name());

    // Good place for unique_ptr and a cast one liner, explicit for example again.
    void *sa_void_object = bj::refractor<void>::make_object("standalone");
    standalone *sa_object = reinterpret_cast<standalone *>(sa_void_object);
    delete sa_object;
}