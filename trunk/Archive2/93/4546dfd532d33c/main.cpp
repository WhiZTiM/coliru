#include <functional>
#include <iostream>

struct abc { int x; abc(int a) : x(a) {} };
struct def { int x; def(int a) : x(a) {} };
struct ghc { int x; ghc(int a) : x(a) {} };
        
template<typename... Args>
void fn(void(*)(Args... fn)) {}
        
int main() {
    fn(+[](abc&) {});
    
    int x = 0;
    fn([x](abc&, def&) {});
}