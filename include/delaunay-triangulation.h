#ifndef DELAUNAY_TRIANGULATION_LIB_H
#define DELAUNAY_TRIANGULATION_LIB_H

#include <type_traits>
#include <array>
#include <vector>
#include <tuple>
#include <optional>
#include <ostream>
#include <string>
#include <algorithm>

template<typename T>
concept Floating = std::is_floating_point_v<T>;

template<typename T>
concept Integral = std::integral<T>;

template<typename T>
concept Numeric = Integral<T> || Floating<T>;


template<Numeric Float>
class Vertex{
private:
    std::array<Float, 2> pos_m;
public:
    Vertex() = default;
    Vertex(const Vertex&) = default;
    Vertex(Vertex&&) = default;
    ~Vertex() = default;

    Vertex(Float x, Float y)
     : pos_m{x, y}
    {}

    Vertex(std::array<Float, 2> l)
     : pos_m(l)
    {}

    Vertex& operator=(const Vertex&) = default;
    Vertex& operator=(Vertex&&) = default;

    bool operator==(const Vertex& b) const
    {
        return this->pos_m == b.pos_m;
    }
    bool operator!=(const Vertex& b) const
    {
        return !(*this == b);
    }

    std::string to_string() const
    {
        return "(" + std::to_string(pos_m[0]) + ", " + std::to_string(pos_m[1]) + ")";
    }

    friend std::ostream& operator<<(std::ostream& os, const Vertex& a)
    {
        os << a.to_string();
        return os;
    }
};

template<Numeric Float>
class Edge{
private:
    std::array<Float, 2> vertices_m;
public:
    Edge() = default;
    Edge(const Edge&) = default;
    Edge(Edge&&) = default;
    ~Edge() = default;

    Edge(const Vertex<Float>& a, const Vertex<Float>& b)
     : vertices_m{a, b}
    {}

    Edge(std::initializer_list<Vertex<Float>> l)
     : vertices_m{l}
    {}

    Edge& operator=(const Edge&) = default;
    Edge& operator=(Edge&&) = default;

    bool operator==(const Edge& b) const
    {
        return std::ranges::any_of(b.vertices_m, [&] (const Vertex<Float>& v) {return v == this->vertices_m[0];})
            && std::ranges::any_of(b.vertices_m, [&] (const Vertex<Float>& v) {return v == this->vertices_m[1];});
    }

    bool operator!=(const Edge& b) const
    {
        return !(*this == b);
    }

    std::string to_string() const
    {
        return "{" + vertices_m[0].to_string() + " <-> " + vertices_m[1].t_string() + "}";
    }

    friend std::ostream& operator<<(std::ostream& os, const Edge& a)
    {
        os << a.to_string();
        return os;
    }

    auto vertices() const
    {
        return vertices_m;
    }
    auto begin()
    {
        return vertices_m.begin();
    }
    auto cbegin()
    {
        return vertices_m.cbegin();
    }
    auto rbegin()
    {
        return vertices_m.rbegin();
    }

    auto end()
    {
        return vertices_m.end();
    }
    auto cend()
    {
        return vertices_m.cend();
    }
    auto rend()
    {
        return vertices_m.rend();
    }

    auto& front()
    {
        return vertices_m.front();
    }
    auto& back()
    {
        return vertices_m.back();
    }
};

template<>
class Edge<size_t>{
   using Int = size_t;
private:
    std::array<Int, 2> vertex_indices_m;
public:
    Edge() = default;
    Edge(const Edge&) = default;
    Edge(Edge&&) = default;
    ~Edge() = default;

    Edge(const Int& a, const Int& b)
     : vertex_indices_m{a, b}
    {}

    Edge(std::array<Int, 2> l)
     : vertex_indices_m{l}
    {}

    Edge& operator=(const Edge&) = default;
    Edge& operator=(Edge&&) = default;

    bool operator==(const Edge& b) const
    {
        return std::ranges::any_of(b.vertex_indices_m, [&] (const Int& v) {return v == this->vertex_indices_m[0];})
            && std::ranges::any_of(b.vertex_indices_m, [&] (const Int& v) {return v == this->vertex_indices_m[1];});
    }

    bool operator!=(const Edge& b) const
    {
        return !(*this == b);
    }

    std::string to_string() const
    {
        return "{" + std::to_string(vertex_indices_m[0]) + " <-> " + std::to_string(vertex_indices_m[1]) + "}";
    }

    friend std::ostream& operator<<(std::ostream& os, const Edge& a)
    {
        os << a.to_string();
        return os;
    }

    auto vertices() const
    {
        return vertex_indices_m;
    }

    auto begin()
    {
        return vertex_indices_m.begin();
    }
    auto cbegin()
    {
        return vertex_indices_m.cbegin();
    }
    auto rbegin()
    {
        return vertex_indices_m.rbegin();
    }

    auto end()
    {
        return vertex_indices_m.end();
    }
    auto cend()
    {
        return vertex_indices_m.cend();
    }
    auto rend()
    {
        return vertex_indices_m.rend();
    }

    auto& front()
    {
        return vertex_indices_m.front();
    }
    auto& back()
    {
        return vertex_indices_m.back();
    }
};

template<Numeric Float>
class Triangle{
private:
    std::array<Vertex<Float>, 3> vertices_m;
public:
    Triangle() = default;
    Triangle(const Triangle&) = default;
    Triangle(Triangle&&) = default;
    ~Triangle() = default;

    Triangle(const Vertex<Float>& a, const Vertex<Float>& b, const Vertex<Float>& c)
     : vertices_m{a, b, c}
    {}

    Triangle(std::array<Vertex<Float>, 3> l)
     : vertices_m{l}
    {}

    Triangle& operator=(const Triangle&) = default;
    Triangle& operator=(Triangle&&) = default;

    bool operator==(const Triangle& b) const
    {
        return std::ranges::any_of(b.vertices_m, [&] (const Vertex<Float>& v) {return v == this->vertices_m[0];})
            && std::ranges::any_of(b.vertices_m, [&] (const Vertex<Float>& v) {return v == this->vertices_m[1];})
            && std::ranges::any_of(b.vertices_m, [&] (const Vertex<Float>& v) {return v == this->vertices_m[2];});
    }

    bool operator!=(const Triangle & b) const
    {
        return !(*this == b);
    }

    std::string to_string() const
    {
        return "[" + vertices_m[0].to_string() + " <-> " +
                     vertices_m[1].to_string() + " <-> " +
                     vertices_m[2].to_string() + "]";
    }

    friend std::ostream& operator<<(std::ostream& os, const Triangle& a)
    {
        os << a.to_string();
        return os;
    }

    auto vertices() const
    {
        return vertices_m;
    }

    auto begin()
    {
        return vertices_m.begin();
    }
    auto cbegin()
    {
        return vertices_m.cbegin();
    }
    auto rbegin()
    {
        return vertices_m.rbegin();
    }

    auto end()
    {
        return vertices_m.end();
    }
    auto cend()
    {
        return vertices_m.cend();
    }
    auto rend()
    {
        return vertices_m.rend();
    }

    auto& front()
    {
        return vertices_m.front();
    }
    auto& back()
    {
        return vertices_m.back();
    }


};
template<>
class Triangle<size_t>{
    using Int = size_t;
private:
    std::array<Int, 3> vertex_indices_m;
public:
    Triangle() = default;
    Triangle(const Triangle&) = default;
    Triangle(Triangle&&) = default;
    ~Triangle() = default;

    Triangle(const Int& a, const Int& b, const Int& c)
     : vertex_indices_m{a, b, c}
    {}

    Triangle(std::array<Int, 3> l)
     : vertex_indices_m{l}
    {}

    Triangle& operator=(const Triangle&) = default;
    Triangle& operator=(Triangle&&) = default;

    bool operator==(const Triangle& b) const
    {
        return std::ranges::any_of(b.vertex_indices_m, [&] (const Int& v) {return v == this->vertex_indices_m[0];})
            && std::ranges::any_of(b.vertex_indices_m, [&] (const Int& v) {return v == this->vertex_indices_m[1];})
            && std::ranges::any_of(b.vertex_indices_m, [&] (const Int& v) {return v == this->vertex_indices_m[2];});
    }

    bool operator!=(const Triangle & b) const
    {
        return !(*this == b);
    }

    std::string to_string() const
    {
        return "[" + std::to_string(vertex_indices_m[0]) + " <-> " +
                     std::to_string(vertex_indices_m[1]) + " <-> " +
                     std::to_string(vertex_indices_m[2]) + "]";
    }

    auto vertices() const
    {
        return vertex_indices_m;
    }

    friend std::ostream& operator<<(std::ostream& os, const Triangle& a)
    {
        os << a.to_string();
        return os;
    }

    auto begin()
    {
        return vertex_indices_m.begin();
    }
    auto cbegin()
    {
        return vertex_indices_m.cbegin();
    }
    auto rbegin()
    {
        return vertex_indices_m.rbegin();
    }

    auto end()
    {
        return vertex_indices_m.end();
    }
    auto cend()
    {
        return vertex_indices_m.cend();
    }
    auto rend()
    {
        return vertex_indices_m.rend();
    }

    auto& front()
    {
        return vertex_indices_m.front();
    }
    auto& back()
    {
        return vertex_indices_m.back();
    }

};

template<Numeric Float, Integral Int>
class Delaunay{
private:
    std::vector<Vertex<Float>> vertices_m;
    std::vector<Edge<Int>> edges_m;
    std::vector<Triangle<Int>> triangles_m;
public:
    Delaunay() = default;
    Delaunay(const Delaunay&) = default;
    Delaunay(Delaunay&&) = default;

    ~Delaunay() = default;

    Delaunay& operator=(const Delaunay&) = default;
    Delaunay& operator=(Delaunay&&) = default;

    std::vector<Vertex<Float>> vertices() const
    {
        return vertices_m;
    }

    std::vector<Edge<Int>> edges() const
    {
        return edges_m;
    }

    std::vector<Triangle<size_t>> triangles() const
    {
        return triangles_m;
    }

    std::vector<Edge<Float>> edges_coord() const
    {
        std::vector<Edge<Float>> res;
        std::transform(std::begin(this->edges_m), std::end(this->edges_m), std::begin(res),
            [&] (const Edge<Int>& vertex_indices)
            {
                return Edge<Float>{vertices_m[vertex_indices[0]], vertices_m[vertex_indices[1]]};
            }
        );
        return res;
    }

    std::vector<Triangle<Float>> triangles_coord() const
    {
        std::vector<Triangle<Float>> res;
        std::transform(std::begin(this->triangles_m), std::end(this->triangles_m), std::begin(res),
            [&] (const Triangle<Int>& vertex_indices)
            {
                return Triangle<Float>{
                    vertices_m[vertex_indices[0]],
                    vertices_m[vertex_indices[1]],
                    vertices_m[vertex_indices[2]]};
            }
        );
        return res;
    }

    std::tuple<Triangle<Int>, Triangle<Int>> flip(const Triangle<Int>& t1, const Triangle<Int>& t2)
    {
        auto ta = t1;
        auto tb = t2;

        for(auto it = std::begin(ta); it != std::end(ta); it++){
            if(std::find(std::begin(tb), std::end(tb), *it) == std::end(tb)){
                std::swap(ta.front(), *it);
            }
        }
        for(auto it = std::begin(tb); it != std::end(tb); it++){
            if(std::find(std::begin(ta), std::end(ta), *it) == std::end(ta)){
                std::swap(tb.front(), *it);
            }
        }

        auto [a, b, c] = ta.vertices();
        auto d = tb.front();
        return {{b, a, d}, {c, d, a}};
    }

    void triangulate(const std::vector<Vertex<Float>>& points);
};
#endif //DELAUNAY_TRIANGULATION_LIB_H
