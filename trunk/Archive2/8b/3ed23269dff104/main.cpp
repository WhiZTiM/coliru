#include <iostream>


//Constexpr Fibonacci
constexpr size_t fibConstexpr(size_t n)
{
    return n <= 2 ? 1 : fibConstexpr(n-1) + fibConstexpr(n-2);
}


//Template Metaprogramming Fibonacci
template <size_t N>
struct fibStruct;

template <>
struct fibStruct<1>
{
    const static size_t value = 1;
};

template <>
struct fibStruct<2>
{
    const static size_t value = 1;
};

template <size_t N>
struct fibStruct
{
    const static size_t value = fibStruct<N-1>::value + fibStruct<N-2>::value;
};


int main()
{
    /*
    static int fibConstexpr40 = fibConstexpr(40);
    //std::cout << fibConstexpr40 << std::endl;
    return fibConstexpr40;
    static_assert(fibConstexpr(46) == 1836311903, "Constexpr Fibonacci no functiona");
    */
    /*
    static int fibStruct40 = fibStruct<40>::value;
    //std::cout << fibStruct40 << std::endl;
    return fibStruct40;
    static_assert(fibStruct<46>::value == 1836311903, "TMP Fibonacci no functiona");
    */
}