#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <array>

namespace geometry {

// Можно написать сложную обёртку с некоторым дополнительным функционалом
// (по типу вычисления нормы, различных арифм. операций и т.д.),
// но на данный момент обойдёмся простым синонимом.
template<class T>
using vertex2D = std::array<T, 2>;
    
} // namespace geometry

#endif