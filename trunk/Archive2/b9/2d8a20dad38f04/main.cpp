#include <algorithm>
#include <iostream>
#include <vector>

struct S {
    S(int x, int y) : x(x), y(y) {}
    int x;
    int y;
};

bool sortByX(const S& lhs, const S& rhs) {
    return lhs.x < rhs.x;
}

bool sortByY(const S& lhs, const S& rhs) {
    return lhs.y < rhs.y;
}

void print(const std::vector<S>& v) {
    for( const S& s : v ) 
        std::cout << s.x << ":" << s.y << ' ';
    std::cout << std::endl;
}

int main()  {
    
    std::vector<S> v{ S(1,200), S(2,100) };
    print(v); // Исходное состояние
    
    std::sort( v.begin(), v.end(), sortByY );
    print(v); // После сортировки по полю Y
    
    std::sort( v.begin(), v.end(), sortByX );
    print(v); // После сортировки по полю X
}