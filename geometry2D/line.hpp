#ifndef LINE_HPP
#define LINE_HPP

#include "polygon.hpp"

namespace geometry {

// Подробно описывать этот класс не стал по той же причине, что и vertex2D и класс point.
// Здесь так же можно навязать много дополнительной логики.
template<class T>
using line = polygon<T, 2>;

}

#endif