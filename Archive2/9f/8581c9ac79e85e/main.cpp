#include <iostream>
#include <algorithm>

struct S
{
    int a;
    int b;
    int c;
};

bool order_by_a(const S& lhs, const S& rhs)
{
    return lhs.a < rhs.a;   
}

std::ostream& operator<<(std::ostream& out, const S& s)
{
    return out << '(' << s.a << ", " << s.b << ", " << s.c << ')';
}

int main()
{
    S array[3] = {{1, 0, 5}, {5, 2, 3}, {2, 1, 4},};
    
    for(const auto& s: array)
        std::cout << s << '\n';
    std::cout << '\n'; 
    
    using std::begin;
    using std::end;
    //http://en.cppreference.com/w/cpp/algorithm/sort
    //Sort by a using comparison function
    std::sort(begin(array), end(array), order_by_a);
    for(const auto& s: array)
        std::cout << s << '\n';
    std::cout << '\n'; 
    
    //Sort by c using lambda function
    std::sort(begin(array), end(array), 
              [](auto& lhs, auto& rhs) { return lhs.c < rhs.c; });
    for(const auto& s: array)
        std::cout << s << '\n';
    std::cout << '\n'; 
}