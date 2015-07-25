#include <algorithm>
#include <iostream>
#include <vector>


struct Tuple
{
    Tuple(int a, int b, int c, int d) : a(a), b(b), c(c), d(d) {}
    int a, b, c, d;
};

bool operator==(Tuple lhs, Tuple rhs)
{
    bool result = true;
    result &= lhs.a == rhs.a;
    result &= lhs.b == rhs.b;
    result &= lhs.c == rhs.c;
    result &= lhs.d == rhs.d;
    return result;
}

int compare(Tuple lhs, Tuple rhs)
{
    int result = 0;
    result += 8 * ((lhs.a > rhs.a) - (lhs.a < rhs.a));
    result += 4 * ((lhs.b > rhs.b) - (lhs.b < rhs.b));
    result += 2 * ((lhs.c > rhs.c) - (lhs.c < rhs.c));
    result += 1 * ((lhs.d > rhs.d) - (lhs.d < rhs.d));
    return result;
}

bool operator<(Tuple lhs, Tuple rhs)
{
    return compare(lhs, rhs) < 0;
}

bool operator<=(Tuple lhs, Tuple rhs)
{
    return compare(lhs, rhs) <= 0;
}

std::ostream& operator<<(std::ostream& os, const Tuple& tuple)
{
    return os << tuple.a << tuple.b << tuple.c << tuple.d;
}



int main()
{
    std::vector<Tuple> tuples;
    
    for (auto i = 0; i != 2; ++i)
    for (auto j = 0; j != 2; ++j)
    for (auto k = 0; k != 2; ++k)
    for (auto l = 0; l != 2; ++l)
        tuples.emplace_back(i, j, k, l);

                    
    auto tuples2 = tuples;
    std::reverse(tuples2.begin(), tuples2.end());
    
    for (auto i = 0 * tuples.size(); i != tuples.size(); ++i)
    {
        auto c = compare(tuples[i], tuples2[i]);
        std::cout << tuples[i] << (c < 0 ? " < " : c == 0 ? " == " : " > ") << tuples2[i] << " (" << c << ")\n";
    }
}

