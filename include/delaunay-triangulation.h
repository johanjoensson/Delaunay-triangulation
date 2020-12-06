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
#include <numeric>
#include <initializer_list>

template<typename T>
concept Floating = std::is_floating_point_v<T>;

template<typename T>
concept Integral = std::integral<T>;

template<typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

template<Numeric Float>
class Edge;
template<>
class Edge<size_t>;

template<Numeric Float>
class Triangle;
template<>
class Triangle<size_t>;




template<Numeric Float, size_t Dim = 2>
class Vertex{
  using Vec = std::array<Float, Dim>;
private:
    Vec pos_m;
public:
    Vertex() = default;
    Vertex(const Vertex&) = default;
    Vertex(Vertex&&) = default;
    ~Vertex() = default;
    Vertex(std::initializer_list<Float> l)
     : pos_m()
    {
      std::copy(l.begin(), l.end(), pos_m.begin());
    }
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
        std::string res = "(";
        for(size_t i = 0; i < Dim; i++){
          res += std::to_string(this->pos_m[i]);
          if(i < Dim -1){
            res += ", ";
          }
        }
        res += ")";
        return res;
    }

    friend std::ostream& operator<<(std::ostream& os, const Vertex& a)
    {
        os << a.to_string();
        return os;
    }

    auto begin()
    {
        return pos_m.begin();
    }
    auto begin() const
    {
        return pos_m.begin();
    }

    auto cbegin()
    {
        return pos_m.cbegin();
    }
    auto rbegin()
    {
        return pos_m.rbegin();
    }
    auto rbegin() const
    {
        return pos_m.rbegin();
    }

    auto end()
    {
        return pos_m.end();
    }
    auto end() const
    {
        return pos_m.end();
    }

    auto cend()
    {
        return pos_m.end();
    }
    auto rend()
    {
        return pos_m.cend();
    }
    auto rend() const
    {
        return pos_m.cend();
    }

    auto& front()
    {
        return pos_m.front();
    }

    auto& back()
    {
        return pos_m.back();
    }
};

template<Numeric Float, size_t Dim = 2>
Float dist2(const Vertex<Float, Dim>& a, const Vertex<Float, Dim>& b)
{
    Vertex<Float, Dim> diff;
    std::transform(std::begin(a), std::end(a), std::begin(b), std::begin(diff),
    [] (const Float& ai, const Float& bi)
        {
            return (bi-ai)*(bi-ai);
        });
    Float res = 0;
    std::accumulate(std::begin(diff), std::end(diff), res, std::plus());
    return res;

}

template<Numeric Float>
class Edge{
private:
    std::array<Vertex<Float>, 2> vertices_m;
public:
    Edge() = default;
    Edge(const Edge&) = default;
    Edge(Edge&&) = default;
    ~Edge() = default;
    Edge(const Vertex<Float>& a, const Vertex<Float>& b)
     : vertices_m{a, b}
    {}
    Edge(std::initializer_list<Vertex<Float>> l)
     : vertices_m()
    {
      std::copy(l.begin(), l.end(), vertices_m.begin());
    }

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
    auto& vertices() const
    {
        return vertices_m;
    }
    auto begin()
    {
        return vertices_m.begin();
    }
    auto begin() const
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
    auto rbegin() const
    {
        return vertices_m.rbegin();
    }

    auto end()
    {
        return vertices_m.end();
    }
    auto end() const
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
    auto rend() const
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
    std::array<Int, 2> neighbors_m;
public:
    Edge() = default;
    Edge(const Edge&) = default;
    Edge(Edge&&) = default;
    ~Edge() = default;

    Edge(const Int& a, const Int& b)
     : vertex_indices_m{a, b}, neighbors_m()
    {}

    Edge(std::initializer_list<Int> l)
     :  vertex_indices_m(), neighbors_m()
    {
      std::copy(l.begin(), l.end(), vertex_indices_m.begin());
    }

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

    auto& vertices() const
    {
        return vertex_indices_m;
    }

    auto begin()
    {
        return vertex_indices_m.begin();
    }
    auto begin() const
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
    auto end() const
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
    auto rend() const
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
class Triangle {
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

    Triangle(std::initializer_list<Vertex<Float>> l)
     : vertices_m()
    {
      std::copy(l.begin(), l.end(), vertices_m.begin());
    }

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
    auto begin() const
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
    auto rbegin() const
    {
        return vertices_m.rbegin();
    }

    auto end()
    {
        return vertices_m.end();
    }
    auto end() const
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
    auto rend() const
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
    std::array<std::optional<Int>, 3> neighbors_m;
public:
    Triangle() = default;
    Triangle(const Triangle&) = default;
    Triangle(Triangle&&) = default;
    ~Triangle() = default;

    Triangle(const Int& a, const Int& b, const Int& c)
     : vertex_indices_m{a, b, c}, neighbors_m()
    {}

    Triangle(const Int& a, const Int& b, const Int& c, const Int& na, const Int& nb, const Int& nc)
     : vertex_indices_m{a, b, c}, neighbors_m{na, nb, nc}
    {}


    Triangle(std::initializer_list<Int> v)
     : vertex_indices_m(), neighbors_m()
    {
      std::copy(v.begin(), v.end(), vertex_indices_m.begin());
    }

    Triangle(std::initializer_list<Int> v, std::initializer_list<Int> n)
     : vertex_indices_m(), neighbors_m()
    {
      std::copy(v.begin(), v.end(), vertex_indices_m.begin());
      std::copy(n.begin(), n.end(), neighbors_m.begin());

    }


    Triangle& operator=(const Triangle&) = default;
    Triangle& operator=(Triangle&&) = default;

    bool operator==(const Triangle& b) const
    {
        return std::ranges::any_of(b.vertex_indices_m, [this] (const Int& v) {return v == this->vertex_indices_m[0];})
            && std::ranges::any_of(b.vertex_indices_m, [this] (const Int& v) {return v == this->vertex_indices_m[1];})
            && std::ranges::any_of(b.vertex_indices_m, [this] (const Int& v) {return v == this->vertex_indices_m[2];});
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

    void cycle(Int step = 1)
    {
        Int n = step % vertex_indices_m.size();
        std::rotate(vertex_indices_m.begin(), vertex_indices_m.begin() + n, vertex_indices_m.end());
        std::rotate(neighbors_m.begin(), neighbors_m.begin() + n, neighbors_m.end());
    }


    auto& vertices() const
    {
        return vertex_indices_m;
    }
    auto& vertices()
    {
        return vertex_indices_m;
    }

    auto& neighbors() const
    {
        return neighbors_m;
    }
    auto& neighbors()
    {
        return neighbors_m;
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
    auto begin() const
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
    auto rbegin() const
    {
        return vertex_indices_m.rbegin();
    }

    auto end()
    {
        return vertex_indices_m.end();
    }
    auto end() const
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
    auto rend() const
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
class Circle{
private:
    Vertex<Float> center_m;
    Float r2_m;
public:
    Circle() = default;
    Circle(const Circle&) = default;
    Circle(Circle&&) = default;

    Circle(const Vertex<Float>& center, const Float& r)
     : center_m(center), r2_m(r*r)
    {}

    Circle(const Vertex<Float>& a, const Vertex<Float>& b, const Vertex<Float>& c)
     : center_m(), r2_m()
    {}

    bool contains(const Vertex<Float>& p)
    {
        return dist2(p, center_m) < r2_m;
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
        for(auto t : triangles_m){
            auto [ai, bi, ci] = t.vertices();
            res.push_back({vertices_m[ai], vertices_m[bi], vertices_m[ci]});
        }
        return res;
    }

    bool circumcircle_contains(const Triangle<Int>& t, const Vertex<Float>& p)
    {
        auto [ai, bi, ci] = t.vertices();
        Vertex<Float> a = this->vertices_m[ai], b = this->vertices_m[bi], c = this->vertices_m[ci];
        Float ax = *a.begin(), ay = *(++a.begin());
        Float bx = *b.begin(), by = *(++b.begin());
        Float cx = *c.begin(), cy = *(++c.begin());
        Float px = *p.begin(), py = *(++p.begin());
        return    (ax - px)*(by - py)*((cx - px)*(cx - px) + (cy - py)*(cy - py))
                + (cx - px)*(ay - ay)*((bx - px)*(bx - px) + (by - py)*(by - py))
                + (bx - px)*(cy - ay)*((ax - px)*(ax - px) + (ay - py)*(ay - py))
                - (cx - px)*(by - ay)*((ax - px)*(ax - px) + (ay - py)*(ay - py))
                - (ax - px)*(cy - ay)*((bx - px)*(bx - px) + (by - py)*(by - py))
                - (bx - px)*(ay - ay)*((cx - px)*(cx - px) + (cy - py)*(cy - py))
                 < 0;
    }

    std::tuple<Float, Float> triangle_edge_checks(const Triangle<Int>& t, const Vertex<Float>& p)
    {
        auto [ai, bi, ci] = t.vertices();
        Vertex<Float> a = this->vertices_m[ai], b = this->vertices_m[bi], c = this->vertices_m[ci];
        Float ax = *a.begin(), ay = *(a.begin() + 1);
        Float bx = *b.begin(), by = *(b.begin() + 1);
        Float cx = *c.begin(), cy = *(c.begin() + 1);
        Float px = *p.begin(), py = *(p.begin() + 1);

        Float det12 = (bx - ax)*(cy - ay) - (by - ay)*(cx - ax);
        Float detp1 = (px)*(by - ay) - (py)*(bx - ax);
        Float detp2 = (px)*(cy - ay) - (py)*(cx - ax);
        Float det01 = (ax)*(by - ay) - (ay)*(bx - ax);
        Float det02 = (ax)*(cy - ay) - (ay)*(cx - ax);

        Float x = (detp2 - det02)/det12;
        float y = -(detp1 - det01)/det12;
        return {x, y};
    }

    bool triangle_contains(const Triangle<Int>& t, const Vertex<Float>& p)
    {
        auto [a, b] = triangle_edge_checks(t, p);
        std::cout << "a = " << a << ", b = " << b << "\n";
        return (std::abs(a) < 1e-10 || a >= 0) && (std::abs(b) < 1e-10 || b >= 0)
            && (std::abs(a + b - 1) < 1e-10 || a + b < 1);
    }

    std::tuple<Triangle<Int>, Triangle<Int>, Triangle<Int>> insert(const Int p, const Triangle<Int> t)
    {
        auto [a, b, c] = t.vertices();
        return {{p, b, c}, {a, p, c}, {a, b, p}};
    }

    std::tuple<Triangle<Int>, Triangle<Int>, Triangle<Int>, Triangle<Int>> insert(const Int p, const Triangle<Int>& t1, const Triangle<Int>& t2)
    {

        auto ta = t1;
        auto tb = t2;

        // Rotate both triangles so that their unique vertices are placed first
        for(auto it = std::begin(ta); it != std::end(ta); it++){
            if(std::find(std::begin(tb), std::end(tb), *it) == std::end(tb)){
                ta.cycle(std::distance(std::begin(ta), it));
            }
        }
        for(auto it = std::begin(tb); it != std::end(tb); it++){
            if(std::find(std::begin(ta), std::end(ta), *it) == std::end(ta)){
                tb.cycle(std::distance(std::begin(tb), it));
            }
        }
        auto [a, b, c] = ta.vertices();
        auto d = tb.front();
        return {{a, b, p}, {b, d,  p}, {b, c, p}, {c, a, p}};
    }


    std::tuple<Triangle<Int>, Triangle<Int>> flip(const Triangle<Int>& t1, const Triangle<Int>& t2)
    {
        auto ta = t1;
        auto tb = t2;

        // Rotate both triangles so that their unique vertices are placed first
        for(auto it = std::begin(ta); it != std::end(ta); it++){
            if(std::find(std::begin(tb), std::end(tb), *it) == std::end(tb)){
                ta.cycle(std::distance(std::begin(ta), it));
            }
        }
        for(auto it = std::begin(tb); it != std::end(tb); it++){
            if(std::find(std::begin(ta), std::end(ta), *it) == std::end(ta)){
                tb.cycle(std::distance(std::begin(tb), it));
            }
        }

        auto [a, b, c] = ta.vertices();
        auto d = tb.front();
        auto [naa, nab, nac] = ta.neighbors();
        auto [nbd, nbc, nbb] = tb.neighbors();
        return {{{b, d, a}, {naa, nac, nbc}}, {{c, d, a}, {nab, nbd, nbb}}};
    }

    Triangle<Float> initial_triangle(const std::vector<Vertex<Float>>& points)
    {
        Float xmin, xmax, ymin, ymax;
        Vertex<Float> p0 = points.front();
        auto xmax_it = std::max_element(std::begin(points), std::end(points),
            [](const Vertex<Float>& a, const Vertex<Float>& b)
            {
                return *a.begin() < *b.begin();
            });
        xmax = *(*xmax_it).begin();
        auto ymax_it = std::max_element(std::begin(points), std::end(points),
            [](const Vertex<Float>& a, const Vertex<Float>& b)
            {
                return *(a.begin() + 1) < *(b.begin() + 1);
            });
        ymax = *((*ymax_it).begin() + 1);
        auto xmin_it = std::min_element(std::begin(points), std::end(points),
            [](const Vertex<Float>& a, const Vertex<Float>& b)
            {
                return *a.begin() < *b.begin();
            });
        xmin = *(*xmin_it).begin();
        auto ymin_it = std::min_element(std::begin(points), std::end(points),
            [](const Vertex<Float>& a, const Vertex<Float>& b)
            {
                return *(a.begin() + 1) < *(b.begin() + 1);
            });
        ymin = *((*ymin_it).begin() + 1);

        std::cout << "xmin = " << xmin << ", xmax = " << xmax << "\n";
        std::cout << "ymin = " << ymin << ", ymax = " << ymax << "\n";

        Float dx = (xmax - xmin)/2, dy = (ymax - ymin);

        return {{xmin - dx, ymin}, {xmax + dx, ymin}, {xmin + dx, ymax + dy}};
    }

    void triangulate(const std::vector<Vertex<Float>>& points)
    {
        Triangle<Float> t0 = initial_triangle(points);
        std::cout << "t0 = " << t0 << "\n";
        vertices_m.insert(std::begin(vertices_m), std::begin(t0), std::end(t0));
        triangles_m.push_back({0, 1, 2});

        for(auto p : points){
            std::vector<Triangle<Int>> containers;
            auto t_it = std::begin(triangles_m);
            while(t_it != std::end(triangles_m)){
                t_it = std::find_if(t_it, std::end(triangles_m),
                    [this, p] (const Triangle<Int>& t_i)
                    {
                        return triangle_contains(t_i, p);
                    });
                if(t_it != std::end(triangles_m)){
                    containers.push_back(*(t_it++));
                }
            }
            if(containers.size() == 0){
                std::cout << "Point, " << p << ", not inside any triangle!\n";
                return;
            }else{
                for(auto t : containers){
                    std::cout << "Point, " << p << ", inside triangle, " << t << "\n";
                }
            }

            vertices_m.push_back(p);
            if(containers.size() == 1){
                auto t = containers.front();
                auto t_it = std::find(std::begin(triangles_m), std::end(triangles_m), t);
                auto [t1, t2, t3] = insert(vertices_m.size() - 1, *t_it);
                auto [n1, n2, n3] = t_it->neighbors();
                triangles_m.erase(t_it);
                Int n = triangles_m.size() - 1;
                t1.neighbors() = {n1, n - 1, n};
                t2.neighbors() = {n - 2, n2, n};
                t3.neighbors() = {n - 2, n - 1, n3};
                /***************************************************************
                *
                ***************************************************************/
                triangles_m.push_back(t1);
                triangles_m.push_back(t2);
                triangles_m.push_back(t3);
            }else if(containers.size() == 2){
                auto ta = containers.front(), tb = containers.back();
                auto [t1, t2, t3, t4] = insert(vertices_m.size() - 1, ta, tb);
                auto ta_it = std::find(std::begin(triangles_m), std::end(triangles_m), ta);
                auto tb_it = std::find(std::begin(triangles_m), std::end(triangles_m), tb);
                auto [tan1, tan2, tan3] = ta_it->neighbors();
                auto [tbn1, tbn2, tbn3] = tb_it->neighbors();
                triangles_m.erase(ta_it);
                triangles_m.erase(tb_it);
                Int n = triangles_m.size() - 1;
                t1.neighbors() = {n - 2, n, tan3};
                t2.neighbors() = {n - 1, n - 3, tbn2};
                t3.neighbors() = {n, n - 2, tbn3};
                t4.neighbors() = {n - 3, n - 1, tan2};
                triangles_m.push_back(t1);
                triangles_m.push_back(t2);
                triangles_m.push_back(t3);
                triangles_m.push_back(t4);
            }
        }
        // Remove all triangles containing the vertices of t0
        for(auto it = std::begin(triangles_m); it != std::end(triangles_m);){
            auto [ai, bi, ci] = it->vertices();
            if( ai == 0 || ai == 1 || ai == 2 ||
                bi == 0 || bi == 1 || bi == 2 ||
                ci == 0 || ci == 1 || ci == 2){
                triangles_m.erase(it);
            }else{
                for(Int& i : *it){
                    i -= 3;
                }
                it++;
            }
        }
        // Remove the vertices of t0
        vertices_m.erase(std::begin(vertices_m), std::begin(vertices_m) + 3);
    }
};




namespace std{
  template<Numeric Float>
  string to_string(const Vertex<Float>& v)
  {
    return v.to_string();
  }

  template<class Float>
  string to_string(const Edge<Float>& e)
  {
    return e.to_string();
  }

  template<Numeric Float>
  string to_string(const Triangle<Float>& t){
    return t.to_string();
  }
}

#endif //DELAUNAY_TRIANGULATION_LIB_H
