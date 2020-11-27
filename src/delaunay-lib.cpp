#include <iostream>
#include "delaunay-triangulation.h"

int main()
{
    Triangle<double> t1{{0.0, 0.0}, {1.0, 0.0}, {0.5, 1.0}}, t2{{0.0, 0.0}, {0.5, -1.0}, {1.0, 0.0}};
    std::cout << t1 << " " << t2 << "\n";
    Delaunay<double, size_t> tri;
    auto [ta, tb] = tri.flip({0, 1, 2}, {2, 3, 0});

    std::cout << "ta " << ta << "\n";
    std::cout << "tb " << tb << "\n";
    return 0;
}
