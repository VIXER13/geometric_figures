#ifndef DYNAMIC_POLYGON_HPP
#define DYNAMIC_POLYGON_HPP

#include "polygon_base.hpp"
#include <vector>

namespace geometry {

static constexpr size_t DYNAMIC_POLYGON = 0;

// Полигон с изменяемым числом вершин.
// Хорошо подходит для фигур, которые необходимо динамически аппроксимировать в зависимости от ситуации,
// например круги, эллипсы или ещё более сложные фигуры.
template<class T>
class polygon<T, 0> : public polygon_base<T> {
protected:
    std::vector<vertex2D<T>> _vertices = {};

public:
    polygon(const std::vector<vertex2D<T>>& vertices) :
        _vertices(vertices) {}

    size_t vertex_count() override {
        return _vertices.size();
    }

    void set_vertex(const size_t i, const vertex2D<T>& vertex) override {
        _vertices[i] = vertex;
    }

    void set_vertices(const std::vector<vertex2D<T>>& vertices) {
        _vertices = vertices;
    }

    const vertex2D<T>& get_vertex(const size_t i) override {
        return _vertices[i];
    }
};

template<class T>
using dynamic_polygon = polygon<T, 0>;

}

#endif