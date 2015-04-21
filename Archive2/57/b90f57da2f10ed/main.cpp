#include <iostream>

unsigned int reverse(unsigned int n)
{
    int N = n;
    N = ((N & 0xFFFF0000) >> 16) | ((N & 0x0000FFFF) << 16);
	N = ((N & 0xFF00FF00) >> 8)  | ((N & 0x00FF00FF) << 8);
	N = ((N & 0xF0F0F0F0) >> 4)  | ((N & 0x0F0F0F0F) << 4);
	N = ((N & 0xCCCCCCCC) >> 2)  | ((N & 0x33333333) << 2);
	N = ((N & 0xAAAAAAAA) >> 1)  | ((N & 0x55555555) << 1);
    return N;
}

unsigned int count_leading_zeroes(unsigned int x)
{
    int n = 32;
    unsigned int y;

    y = x >>16; if (y != 0) { n = n -16; x = y; }
    y = x >> 8; if (y != 0) { n = n - 8; x = y; }
    y = x >> 4; if (y != 0) { n = n - 4; x = y; }
    y = x >> 2; if (y != 0) { n = n - 2; x = y; }
    y = x >> 1; if (y != 0) return n - 2;
    return n - x;
}

bool is_palindrome(unsigned int n)
{
	return (reverse(n) >> count_leading_zeroes(n)) == n;
}

int main()
{
    for (unsigned int f = 1900; f <= 2100; ++f)
    {
        if (is_palindrome(f))
    		std::cout << f << " ";
    }
    std::cout << std::endl;
}
