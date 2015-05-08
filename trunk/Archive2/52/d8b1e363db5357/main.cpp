#include <iostream>

struct Example {
    Example() : n(7),
                s("abc"),
                level{{1,2}, {3,4}}
    {}
    int n;
    std::string s;
    int level[2][2];
};

int main()
{
    Example ex;
    std::cout << "n = " << ex.n << "\ns = " << ex.s << "\nlevel =\n";
    for(auto& row: ex.level) {
        for(int n: row) std::cout << n << ' ';
        std::cout << '\n';
   }
}
