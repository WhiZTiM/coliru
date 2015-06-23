#include <iostream>
#include <string>
#include <vector>

#undef RAND_MAX
#define RAND_MAX 4

int xrand() {
    static int n;
    if (++n > RAND_MAX) n = 0;
    return n;
}

unsigned int rand_range(unsigned int max) {
    double v = max > RAND_MAX ? max : RAND_MAX;
    v /= RAND_MAX;

    int n;
    do {
        n = xrand();
    } while (RAND_MAX - n <= RAND_MAX % (unsigned int)(max / v));

    return (unsigned int)(v * n) % max;
}

int main()
{
    for (int i = 1; i < 10; ++i)
    {
        std::cout << "rr(" << i << ") ";
        for (unsigned u = 1; u <= 12; ++u)
            std::cout << rand_range(i) << ' ';
        std::cout << '\n';
    }
            
}
