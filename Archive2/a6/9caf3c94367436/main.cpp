#include <iostream> 

template<typename Arg>
auto hello(Arg a) -> decltype( a.x ) { return a.x; }

template<typename Arg>
auto hello(Arg a) -> decltype( a.y ) { return a.y; }

struct has_x { int x; };
struct has_y { int y; };

template int hello(has_x);
template int hello(has_y);

int main()
{
    has_x x;
    x.x = 10;
    std::cout << hello(x)  << std::endl;
    std::cout << "world" <<std::endl;
}