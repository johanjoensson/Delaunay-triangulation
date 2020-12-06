#include <iostream>
#include "delaunay-triangulation.h"

int main()
{
    Delaunay<double, size_t> tri;
    tri.triangulate({{0.0, 0.0}, {1.0, 0.0}, {0.5, 1.0}, {1.5, 2.0}});
//    auto [ta, tb] = tri.flip({0, 1, 2}, {2, 3, 0});
    std::cout << "Triangles, with vertex indices:\n";
    for(auto t : tri.triangles()){
        std::cout << t <<", ";
    }
    std::cout << "\n";
    std::cout << "Vertices:\n";
    for(auto v : tri.vertices()){
        std::cout << v <<", ";
    }
    std::cout << "\n";
    std::cout << "Triangles, with vertices in coordinates:\n";
    for(auto t : tri.triangles_coord()){
        std::cout << t <<", ";
    }
    std::cout << "\n";

    return 0;
}
