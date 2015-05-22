#include <iostream> 

template<typename Arg>
auto hello(Arg a) -> decltype( a.x ) { return a.x; }

template<typename Arg>
auto hello(Arg a) -> decltype( a.y ) { return a.y; }

struct has_x { int x; };
struct has_y { int y; };

struct has_x_y { int x; int y; };

/*template int hello(has_x);
template int hello(has_y);*/

int main()
{
    has_x x;
    x.x = 10;
    
    has_x_y xy;
    
    xy.x = 20;
    
    std::cout << hello(x)  << std::endl;
    std::cout << hello(xy)  << std::endl;
    std::cout << "world" <<std::endl;
}