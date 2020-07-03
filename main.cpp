#include <iostream>
#include <memory>
#include "polygon.hpp"

void check_polygon(const std::unique_ptr<geometry::polygon_base<double>>& poly) {
    std::cout << "Coordinates: " << std::endl;
    for(size_t i = 0; i < poly->vertex_count(); ++i) {
        geometry::vertex2D<double> vertex = poly->get_vertex(i);
        std::cout << vertex[0] << " " << vertex[1] << std::endl;
    }
    std::cout << "Convex: "    << (poly->convex() ? "yes" : "no") << std::endl
              << "Perimeter: " << poly->perimeter() << std::endl
              << "Area: "      << poly->area() << std::endl;
}

int main() {
    using namespace geometry;

    std::unique_ptr<polygon_base<double>> poly = 
        std::make_unique<dynamic_polygon<double>>(
            dynamic_polygon<double>::container_type{
                vertex2D<double>{-1., -1.},
                vertex2D<double>{ 1., -1.},
                vertex2D<double>{ 1.,  1.},
                vertex2D<double>{-1.,  1.}
            }
        );

    check_polygon(poly);

    std::cout << std::endl << std::endl;

    // Намеренно делаем полигон вырожденным
    poly->set_vertex(0, vertex2D<double>{0., 17});
    check_polygon(poly);

    return EXIT_SUCCESS;
}