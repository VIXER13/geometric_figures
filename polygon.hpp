#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <cmath>
#include <array>
#include <vector>
#include <exception>
#include <algorithm>
#include "power.hpp"

namespace geometry {

template<class T>
using vertex2D = std::array<T, 2>;

template<class T>
class polygon_base {
    static_assert(std::is_floating_point<T>{}, "The T must be floating point.");

protected:
    T oriented_triangle_area(const vertex2D<T>& a, const vertex2D<T>& b, const vertex2D<T>& c) noexcept {
        return (b[0] - a[0]) * (c[1] - a[1]) - (b[1] - a[1]) * (c[0] - a[0]);
    }

    bool intersect(const vertex2D<T>& a, const vertex2D<T>& b, const vertex2D<T>& c, const vertex2D<T>& d) noexcept {
        static constexpr auto check_segment = [](T a, T b, T c, T d) {
            if (a > b) std::swap(a, b);
            if (c > d) std::swap(c, d);
            return std::max(a, c) <= std::min(b, d);
        };
        
        return check_segment(a[0], b[0], c[0], d[0]) && 
               check_segment(a[1], b[1], c[1], d[1]) &&
               oriented_triangle_area(a, b, c) * oriented_triangle_area(a, b, d) <= 0 &&
               oriented_triangle_area(c, d, a) * oriented_triangle_area(c, d, b) <= 0;
    }

public:
    virtual size_t vertex_count() = 0;
    virtual void set_vertex(const size_t i, const vertex2D<T>& vertex) = 0;
    virtual const vertex2D<T>& get_vertex(const size_t i) = 0;

    T perimeter() {
        const size_t N = vertex_count();
        T sum = 0;
        // Вычисляется как сумма длин отрезков между соседними точками.
        for(size_t i = 0, j = N-1; i < N; ++i, j = (i+1) % N) {
            const vertex2D<T> &pi = get_vertex(i),
                              &pj = get_vertex(j);
            sum += sqrt(metamath::power<2>(pi[0] - pj[0]) + metamath::power<2>(pi[1] - pj[1]));
        }
        return sum;
    }

    // Вычисление площади фигуры
    T area(const bool check = true) {
        // Если стороны самопересекающиеся, то кидается исключение
        if (check && self_crossing()) {
            throw std::domain_error{"self crossing"};
        }

        const size_t N = vertex_count();
        T sum = 0;
        // Вычисляется по формуле площади Гаусса
        for(size_t i = 0, j = N-1; i < N; ++i, j = (i+1) % N) {
            const vertex2D<T> &pi = get_vertex(i),
                              &pj = get_vertex(j);
            sum += pi[0] * pj[1] - pj[0] * pi[1];
        }
        return 0.5 * sum;
    }

    // Проверка выпуклости
    bool convex() {
        const size_t N = vertex_count();
        bool left = false, right = false;
        for(size_t i = 0; i < N; ++i) {
            if(oriented_triangle_area(get_vertex(i), get_vertex((i + 1) % N), get_vertex((i + 2) % N)) < 0) {
                left = true;
            } else {
                right = true;
            }
        }
        return left ^ right;
    }

    // Проверка самопересечения сторон
    bool self_crossing() {
        const size_t N = vertex_count();
        for(size_t i = 0; i < N-2; ++i) {
            for(size_t j = i+2; j < N-1; ++j) {
                if(intersect(get_vertex(i), get_vertex(i+1), get_vertex(j), get_vertex(j+1))) {
                    return true;
                }
            }
        }
        return false;
    }
};

template<class T, size_t N>
class polygon : public polygon_base<T> {
    static_assert(N != 1 && N != 2, "N must be greather than 2.");

public:
    // В случае если задан 0, полигон становится динамическим и может иметь произвольное число вершин.
    using container_type = std::conditional_t<N == 0, std::vector<vertex2D<T>>,
                                                      std::array<vertex2D<T>, N>>;

private:
    container_type _vertices = {};

public:
    polygon(const container_type& vertices) :
        _vertices(vertices) {}

    size_t vertex_count() override {
        return _vertices.size();
    }

    void set_vertex(const size_t i, const vertex2D<T>& vertex) override {
        _vertices[i] = vertex;
    }

    void set_vertices(const container_type& vertices) {
        _vertices = vertices;
    }

    const vertex2D<T>& get_vertex(const size_t i) override {
        return _vertices[i];
    }
};

template<class T>
using dynamic_polygon = polygon<T, 0>;

template<class T>
using triangle = polygon<T, 3>;

}

#endif