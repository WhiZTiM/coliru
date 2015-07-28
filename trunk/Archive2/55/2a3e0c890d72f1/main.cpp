#include <map>
#include <vector>
#include <iostream>

struct A {
    A(int i = 0) : i(i) { }
    A(const A& a) : i(a.i) { std::cout << "A(const A&)\n"; }
    A& operator=(const A& a) { i = a.i; std::cout << "A::operator=(const A&)\n"; return *this; }
    ~A() { std::cout << "~A()\n"; }
    int i;
};
bool operator<(const A& a, const A& b) { return a.i < b.i; }

namespace std {
template<> struct pair<A, std::vector<int>> {
    pair() : first(), second() { }
    pair(const pair&) = default;
    pair(pair&&) = default;
    template<typename T, typename U> pair(const pair<T, U>& p) : first(p.first), second(p.second) { }
    template<typename T, typename U> pair(pair<T, U>&& p) : first(std::move(p.first)), second(std::move(p.second)) { }
    template<typename T, typename U> pair(T&& t, U&& u) : first(std::forward<T>(t)), second(std::forward<U>(u)) { }
    pair& operator=(const pair&) = default;
    pair& operator=(pair&&) = default;
    template<typename T, typename U> pair& operator=(const pair<T, U>& p) { first = p.first; second = p.second; return *this; }
    template<typename T, typename U> pair& operator=(pair<T, U>&& p) { first = std::move(p.first); second = std::move(p.second); return *this; }
    
    A first;
    char padding [16];
    std::vector<int> second;
};
}

int
main()
{
    std::map<A, std::vector<int>> m1;
    m1[A{1}] = {1};
    m1[A{2}] = {2};
    m1[A{3}] = {3};
    std::map<A, std::vector<int>> m2;
    m2[A{4}] = {4};
    m2[A{5}] = {5};
    m2[A{6}] = {6};
    std::cout << "start copy assignment\n";
    m2 = m1;
    std::cout << "end copy assignment\n";
}