#include <iostream>
#include <algorithm>

struct S
{
    int a;
    int b;
    int c;
};

std::ostream& operator<<(std::ostream& out, const S& s)
{
    return out << '(' << s.a << ", " << s.b << ", " << s.c << ')';
}

int get_number(S* array, int row, int column)
{
    switch (column) {
        case 1: return array[row-1].a;   
        case 2: return array[row-1].b;   
        case 3: return array[row-1].c;  
        default: throw "Invalid column";
    }
}

int main()
{
    S array[3] = {{1, 0, 5}, {5, 2, 3}, {2, 1, 4},};
    
    for(const auto& s: array)
        std::cout << s << '\n';
    std::cout << '\n'; 
    
    std::cout << get_number(array, 2, 1) << '\n';
}