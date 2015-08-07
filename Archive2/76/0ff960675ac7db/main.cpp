#include <vector>

int main()
{
    template<class T>
    using test = std::vector<T>;
    
    test x;
    (void) x;
    return 0;
}