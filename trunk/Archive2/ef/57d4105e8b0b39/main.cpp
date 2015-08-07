#include <vector>

int main()
{
    struct foo {
        template<class T>
        using test = std::vector<T>;
    };
    
    foo::test<int> x;
    (void) x;
    return 0;
}