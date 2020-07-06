#ifndef POLYGON_HPP
#define POLYGON_HPP

#include "polygon_base.hpp"

namespace geometry {

// Определение полигонов с заданным числом сторон.
// Имеет несколько специализаций на случай N = 0, 1, 2, 3, 4. (см. dynamic_polygon.hpp, point.hpp, line.hpp, triangle.hpp, quadrangle.hpp)
template<class T, size_t N>
class polygon : public polygon_base<T> {
protected:
    std::array<vertex2D<T>, N> _vertices = {};

public:
    polygon(const T r = 1, const T phi = 0) {
        static constexpr T step = 2 * M_PI / N;
        for(size_t i = 0; i < N; ++i) {
            _vertices[i] = { r * sin(step * i + phi),
                             r * cos(step * i + phi) };
        }
    }

    polygon(const std::array<vertex2D<T>, N>& vertices) :
        _vertices(vertices) {}

    size_t vertex_count() override {
        return _vertices.size();
    }

    void set_vertex(const size_t i, const vertex2D<T>& vertex) override {
        _vertices[i] = vertex;
    }

    void set_vertices(const std::array<vertex2D<T>, N>& vertices) {
        _vertices = vertices;
    }

    const vertex2D<T>& get_vertex(const size_t i) override {
        return _vertices[i];
    }
};

}

#endif