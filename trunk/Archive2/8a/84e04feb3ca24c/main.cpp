#include <set>
#include <list>

template <class Container, class Compare>
auto intersect(const Container& C, Compare cmp) -> decltype(auto)
{
    using K = typename Container::value_type;
    std::set<K, Compare> S(cmp);
    std::list<std::pair<K,K>> L;

    for (auto& s : C) {
        auto it = S.find(s);
        if (it != S.end()) {
            L.emplace_back(std::make_pair(s, *it));
            S.erase(it);
        }
        else S.insert(it, s);
    }
    return L;
}

struct vec2 { int _a, _b; };

inline int cross(const vec2& v1, const vec2& v2) {
    return v1._a * v2._b - v2._a * v1._b; 
}

struct point { int _x, _y; };

inline vec2 operator-(const point& p1, const point& p2) {
    return vec2{p1._x - p2._x, p1._y - p2._y};
}

inline int turn(const point& a, const point& b, const point& c) {
    return cross(a - c, b - c);
}

template <class ostream>
ostream& operator<<(ostream& os, const point& p) { 
    os << '(' << p._x << ", " << p._y << ')'; return os; 
}

struct segment
{
    point _h, _t;
    segment(point h, point t) : _h(h), _t(t) { 
        if (t._y < h._y) std::swap(_h, _t); 
    }
};

template <class ostream>
ostream& operator<<(ostream& os, segment s) { 
    os << '[' << s._h << ", " << s._t << ']'; return os; 
}

#include <iostream>
#include <vector>

/****
\begin{tikzpicture}
\draw (-14,6) -- (-10,3);
\draw[thick, color=blue] (-10,6) -- (-6,3);
\draw (-4,2) -- (-6,4);
\draw[thick, color=blue] (-9,5) -- (-1,3);
\draw (-2,4) -- (-4,3);
\draw (-3,5) -- (2,2);
\draw (3,5) -- (1,3);
\draw (-8,4) -- (-10,2);
\draw[dashed] (-15,3) -- (4,3);
\end{tikzpicture}
***/

int main()
{
    std::vector<segment> S = { 
        {{-14,6}, {-10,3}}, {{-10,6}, {-6,3}},
        {{-4,2}, {-6,4}}, {{-9,5}, {-1,3}},
        {{-2,4}, {-4,3}}, {{-3,5}, {2,2}},
        {{3,5}, {1,3}}, {{-8,4}, {-10,2}},
    };

    auto leftof = [](auto s1, auto s2)-> bool { 
        return (turn(s1._h, s2._t, s2._h) < 0 
            && turn(s1._t, s2._t, s2._h) < 0)
            || (turn(s1._t, s1._h, s2._h) > 0
            && turn(s1._t, s1._h, s2._t) > 0);
    }; /* important! not strict weak ordering in general! */

    auto L = intersect(S, leftof);
    if (L.empty()) std::cout << "No intersect\n";
    else
        for (auto& p : L)
            std::cout << p.first << " and " << p.second << '\n';
    /* 
      output should be:
          [(-1, 3), (-9, 5)] and [(-6, 3), (-10, 6)]
    */
}
