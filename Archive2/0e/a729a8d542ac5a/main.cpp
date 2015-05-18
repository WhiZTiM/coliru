#include <iostream>

namespace N {
    struct Foo {
    };
    
    void swap(Foo& a, Foo& b) {
        std::cout << "user\n";
    }
}

template<class ForwardIt1, class ForwardIt2>
void iter_swap(ForwardIt1 a, ForwardIt2 b)
{
   using std::swap;
   swap(*a, *b);
}

int main() {
    N::Foo x, y;
    iter_swap(&x, &y);
    
    int a, b;
    iter_swap(&a, &b);
}