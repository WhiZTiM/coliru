#include <functional>
#include <iostream>

struct s { int x; };

int main(int argc, char **argv)
{
    std::function<void (s &&)> f = [](const s &p) { std::cout << p.x; };
    f(s {1});
    return 0;
}
