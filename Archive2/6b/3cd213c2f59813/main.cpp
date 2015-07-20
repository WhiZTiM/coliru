#include <iostream>
#include <type_traits>

struct movable
{
    char *a;
    
    movable(char *arg) : a(arg) {}
    
    movable(movable const &) = delete;
    movable &operator=(movable const &) = delete;
};

int main()
{
    std::cout << std::is_nothrow_constructible<movable, char *>::value << std::endl;
}
