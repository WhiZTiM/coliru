#include <iostream>

constexpr long Factorial(long n)
{
    return n > 0 ? n * Factorial(n - 1) : 1;
}

constexpr long CountTrailingZeroes(long N)
{
    return N % 10 == 0 ? 1 + CountTrailingZeroes(N / 10) : 0;
}

template<long N, long Zeroes = CountTrailingZeroes(N)>
struct ZeroCount
{
    const static long Value = Zeroes;
};

constexpr long FindFirstWithZeros(long Zeros, long CurrNum = 0)
{
    return CountTrailingZeroes(Factorial(CurrNum)) == Zeros ? CurrNum : FindFirstWithZeros(Zeros, CurrNum + 1);
}

template<long N, long Num = FindFirstWithZeros(N)>
struct FirstFactorialWithZeroes
{
    const static long Value = Num;
};

int main()
{
    static_assert(FirstFactorialWithZeroes<2>::Value == 10, "Fail"); //Compile-time.
    static_assert(FirstFactorialWithZeroes<3>::Value == 15, "Fail"); //Compile-time.
}
