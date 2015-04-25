#include <unordered_map>
#include <typeindex>
#include <list>
#include <functional>
#include <vector>
#include <memory>
#include <tuple>
#include <algorithm>
#include <iostream>
#include <type_traits>
        
template<typename... Components>
void do_something(void(*)(Components...)) {}
    
struct abc { int x; abc(int a) : x(a) {} };
struct def { int x; def(int a) : x(a) {} };
struct ghc { int x; ghc(int a) : x(a) {} };
        
int main() {
    do_something([](abc&, def&) {});
}