#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "polygon_base.hpp"

namespace geometry {

// Треугольные полигоны в общем виде
template<class T>
class polygon<T, 3> : public polygon_base<T> {
protected:
    std::array<vertex2D<T>, 3> _vertices = {};

public:
    polygon(const T r = 1, const T phi = 0) {
        static constexpr T step = M_PI / 1.5;
        for(size_t i = 0; i < 3; ++i) {
            _vertices[i] = { r * sin(step * i + phi),
                             r * cos(step * i + phi) };
        }
    }

    polygon(const std::array<vertex2D<T>, 3>& vertices) :
        _vertices(vertices) {}

    size_t vertex_count() override {
        return _vertices.size();
    }

    void set_vertex(const size_t i, const vertex2D<T>& vertex) override {
        _vertices[i] = vertex;
    }

    void set_vertices(const std::array<vertex2D<T>, 3>& vertices) {
        _vertices = vertices;
    }

    const vertex2D<T>& get_vertex(const size_t i) override {
        return _vertices[i];
    }
};

template<class T>
using triangle = polygon<T, 3>;

template<class T>
class right_triangle : protected triangle<T> {
protected:
    using triangle<T>::_vertices;

public:
    using triangle<T>::perimeter;

    right_triangle(const T a = 1, const T b = 1) {
        _vertices[0] = {0, 0};
        _vertices[1] = {a, 0};
        _vertices[2] = {0, b};
    }

    T area(const bool check = true) {
        return 0.5 * _vertices[1][0] * _vertices[2][1];
    }
    
    constexpr bool convex() noexcept {
        return true;
    }
    
    constexpr bool self_crossing() noexcept {
        false;
    }
};

}

#endif