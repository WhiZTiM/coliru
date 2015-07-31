// http://stackoverflow.com/questions/31735037/is-there-any-way-for-constexpr-objects-to-refer-point-to-other-non-static-conste
#include <iostream>

constexpr int foo(const int i) { 
    //constexpr   // try to uncomment this and you'll get an error about `i` not being a constant expression
        int j = i*i;
    return j;
}

template<int N>
void output()
{
    std::cout << N << std::endl;
}

int main() { 
    // to be absolutely sure compile time eval'd,
    // pass as template arg
    constexpr auto b = foo(55);
    output<b>();
}
