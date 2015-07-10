#include <iostream>
#include <string>
#include <vector>


class A
{
    int _i;
    int _j;
public:
    A(int i, int j) : _i(i), _j(j) { std::cout << "cons" << std::endl; }

    A(const A& other) { std::cout << "copy cons" << std::endl; }
    
    private:
    A& operator=(const A& other) { std::cout << "operator=" << std::endl; return *this; }
};

int main()
{
    std::vector<A> as{
            { 1, 2 },
            { 1, 3 },
            { 7, 2 },
    };
    return 0;
}
