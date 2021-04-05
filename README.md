# bj::refraction

[![CMake](https://github.com/BetaJester/refraction/actions/workflows/cmake.yml/badge.svg?branch=main)](https://github.com/BetaJester/refraction/actions/workflows/cmake.yml)

A very lightweight header only reflection library for C++.

Follows a core tenet of C++, *You don't pay for what you don't use*. Literally zero cost where not used, minimal cost where it is.

## TOC

* [Example](#example)
* [Refraction?](#refraction)
* [Thing's You Need To Know](#things-you-need-to-know)

## Example

Ignore the bad practices in this example (such as iostream :P) and see the [serializing example](example/serializing/) code for something you can sink your teeth into later.

```cpp
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
```

Output:

```
Object class name: derived
Standalone size: 42
```

## Refraction?

I didn't really need a reflection library, so I took a day to knock this together, for the sole purpose of instantiating objects of a class by name at run time. In the future I may expand this to serve more reflection features.

## Without Macros

You can of course, avoid the use of macros at all, they expand to the following single lines, using the types from the [example](#example).

```cpp
struct base {};

struct derived : base {
    static inline bj::refractor<derived, base> refractor{ "derived" };
};

struct standalone {
    static inline bj::refractor<standalone, void> refractor{ "standalone" };
};
```

## Thing's You Need To Know

* Due to macros, the string needed to find the class is exactly what you pass `BJ_REFRACT_ME` or `BJ_REFRACT_VOID`, meaning if you pass the namespace then it is part of the string, this may actually be something you want. If you don't use macros you can choose any string.
* There is one static object for each class that uses refraction, and one list of registered types per *base type given* and one for `void` used as a base type. To summarize the cost:
  * Classes refracted - one static object.
  * Objects of refracted classes - nothing.
  * Classes used as bases - one static list per base, one entry per refracted derived class.
  * Objects of classes used as bases - nothing.
* Given the above, a game where everything inherits from a minimal number of base game objects has minimal overhead.
* The base type used for `bj::instantiate` must be the base used when creating the object, the one-static-per-template-type system is how this works. If you want the object constructed as another type in the class hierarchy that's a step for you to do safely.