#include <iostream>

class X
    {
        public:
            static int const s_x = 34;
            static int const s_y;
    };

    int const X::s_y = 12;

    int main()
    {
        int const *ix = &X::s_x;    // compiles, but fails to link
        int const *iy = &X::s_y;    // compiles and links correctly
        std::cout << "ix=" << ix << " iy=" << iy << "\n";
    }