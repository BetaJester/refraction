// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/refraction
// for details.


// This file shows a basic example of serializing/deserializing using
// the bj::refraction library, combined with the bj::binaryizer library.

// There is a number of ways to approach this, this is a simple one.


#include <fmt/format.h>
#include <bj/refraction/refractor.hpp>
#include <bj/binaryizer/io/stringstream_binaryizer.hpp>
#include <bj/binaryizer/stl/vector.hpp>
#include <bj/binaryizer/stl/pair.hpp>
#include <bj/binaryizer/stl/basic_string.hpp>

namespace ex {

    class base_shape {
    
    public:

        virtual ~base_shape() noexcept = default;

        virtual void debinaryize(bj::ibinaryizer &in) = 0;
        virtual void binaryize(bj::obinaryizer &out) const = 0;

        virtual void describe() const noexcept = 0;
    
    };

    class triangle : public base_shape {

        BJ_REFRACT_ME(ex::triangle, ex::base_shape);

    public:

        int lengths[3]{};

        void debinaryize(bj::ibinaryizer &in) override {
            in(lengths);
        }

        void binaryize(bj::obinaryizer &out) const override {
            out(refractor.info.name, lengths);
        }

        void describe() const noexcept override {
            fmt::print("Triangle: {}/{}/{}\n", lengths[0], lengths[1], lengths[2]);
        }

    };

    class circle : public base_shape {

        BJ_REFRACT_ME(ex::circle, ex::base_shape);

    public:

        float radius{};

        void debinaryize(bj::ibinaryizer &in) override {
            in(radius);
        }

        void binaryize(bj::obinaryizer &out) const override {
            out(refractor.info.name, radius);
        }

        void describe() const noexcept override {
            fmt::print("Circle: {}\n", radius);
        }

    };

    class polygon : public base_shape {

        BJ_REFRACT_ME(ex::polygon, ex::base_shape);

    public:

        std::vector<std::pair<double, double>> positions;

        void debinaryize(bj::ibinaryizer &in) override {
            in(positions);
        }

        void binaryize(bj::obinaryizer &out) const override {
            out(refractor.info.name, positions);
        }

        void describe() const noexcept override {
            fmt::print("Polygon: ");
            for (auto &position : positions) {
                fmt::print("({}/{}) ", position.first, position.second);
            }
            fmt::print("\n");
        }

    };

} // namespace ex.

void build(bj::obinaryizer &out) {
    ex::triangle triangle;
    triangle.lengths[0] = 2;
    triangle.lengths[1] = 5;
    triangle.lengths[2] = 8;

    ex::circle circle;
    circle.radius = 19.0f;

    ex::polygon polygon;
    polygon.positions.emplace_back(20.9, 12.5);
    polygon.positions.emplace_back(3.6, 46.1);
    polygon.positions.emplace_back(2.3, 765.89);
    polygon.positions.emplace_back(23.75, 1.21);
    polygon.positions.emplace_back(56.12, 0.8);
    polygon.positions.emplace_back(135.0, 12.65);

    out(3u, triangle, circle, polygon);
}

void unbuild(bj::ibinaryizer &in) {

    const auto count = in.get<unsigned int>();
    std::string type;

    for (unsigned int i{}; i < count; ++i) {

        in(type);
        auto shape = bj::instantiate<ex::base_shape>(type);
        in(*shape);
        shape->describe();
    }

}

int main() {

    bj::stringstream_binaryizer iobin;

    build(iobin);

    unbuild(iobin);

}