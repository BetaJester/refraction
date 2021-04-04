# bj::refraction

A very lightweight head only reflection library for C++.

## Example

```cpp
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
```

## Refraction?

I didn't really need a reflection library, so I took a day to knock this together, for the sole purpose of instantiating objects of a class by name at run time. In the future I may expand this to serve more reflection features.

## Gotchas

* Due to macros, the string needed to find the class is exactly what you pass `BJ_REFRACT_ME` or `BJ_REFRACT_VOID`, meaning if you pass the namespace it is part of the string, this may actually be something you want.