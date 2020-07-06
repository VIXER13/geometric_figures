#ifndef POLYGON_BASE_HPP
#define POLYGON_BASE_HPP

#include "vertex.hpp"
#include <cmath>
#include <exception>

namespace geometry {

// Определение полиморфного объекта --- полигон (многоугольник).
template<class T>
class polygon_base {
    static_assert(std::is_floating_point<T>{}, "The T must be floating point.");

protected:
    T oriented_triangle_area(const vertex2D<T>& a, const vertex2D<T>& b, const vertex2D<T>& c) noexcept;
    bool intersect(const vertex2D<T>& a, const vertex2D<T>& b, const vertex2D<T>& c, const vertex2D<T>& d) noexcept;

public:
    virtual ~polygon_base() noexcept = default;

    virtual size_t vertex_count() = 0;
    virtual void set_vertex(const size_t i, const vertex2D<T>& vertex) = 0;
    virtual const vertex2D<T>& get_vertex(const size_t i) = 0;

    T perimeter();
    T area(const bool check = true);
    bool convex();
    bool self_crossing();
};

// Вычисление ориентированной площади треугольника на точках a, b, c.
template<class T>
T polygon_base<T>::oriented_triangle_area(const vertex2D<T>& a, const vertex2D<T>& b, const vertex2D<T>& c) noexcept {
    return (b[0] - a[0]) * (c[1] - a[1]) - (b[1] - a[1]) * (c[0] - a[0]);
}

// Проверка отрезков AB и CD на предмет пересечения.
template<class T>
bool polygon_base<T>::intersect(const vertex2D<T>& a, const vertex2D<T>& b, const vertex2D<T>& c, const vertex2D<T>& d) noexcept {
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

// Вычисление периметра
template<class T>
T polygon_base<T>::perimeter() {
    T sum = 0;
    const size_t N = vertex_count();
    for(size_t i = 0, j = N-1; i < N; ++i, j = (i+1) % N) {
        const vertex2D<T> &pi = get_vertex(i),
                          &pj = get_vertex(j);
        sum += sqrt(std::pow(pi[0] - pj[0], 2) + std::pow(pi[1] - pj[1], 2));
    }
    return sum;
}

// Вычисление площади фигуры по формуле площади Гаусса.
// Данная формула требует, чтобы многоугольник не имел самопересекающихся линий,
// поэтому перед вычислением площади выполняется проверка на самопересечение,
// но так как эта операция весьма дорогая и не всегда необходима,
// пользователь может её отключить выставив параметр check = false.
template<class T>
T polygon_base<T>::area(const bool check) {
    if (check && self_crossing()) {
        throw std::domain_error{"self crossing"};
    }

    T sum = 0;
    const size_t N = vertex_count();
    for(size_t i = 0, j = N-1; i < N; ++i, j = (i+1) % N) {
        const vertex2D<T> &pi = get_vertex(i),
                          &pj = get_vertex(j);
        sum += pi[0] * pj[1] - pj[0] * pi[1];
    }
    return 0.5 * sum;
}

// Проверка выпуклости.
// Многоугольник выпуклый если все ориентированные площади одинаково определены.
template<class T>
bool polygon_base<T>::convex() {
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

// Проверка самопересечения сторон.
// Проверка каждого отрезка с каждым на предмет пересечения.
template<class T>
bool polygon_base<T>::self_crossing() {
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
    
} // namespace geometry

#endif