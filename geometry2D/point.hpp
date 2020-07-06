#ifndef POINT_HPP
#define POINT_HPP

#include "polygon.hpp"

namespace geometry {

// Данный класс должен повторять логику vertex2D, но в то же время удовлетворять интерфейсам polygon.
// Так как я не стал подробно описывать vertex2D, описание этого класса я так же опустил.
template<class T>
using point = polygon<T, 1>;

}

#endif