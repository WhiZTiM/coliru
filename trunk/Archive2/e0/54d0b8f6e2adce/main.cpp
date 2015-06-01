#include <iostream>

using namespace std;

template<size_t size>
class StackMemPolicy
{
private:
    char mem[size];

public:
    typedef char * iter;
    iter begin() 
    {
        return std::begin(mem);
    }
    iter end()
    {
        return std::end(mem);
    }
};

int main()
{
    StackMemPolicy<4> bar;
    for (auto it = bar.begin(); it != bar.end(); ++it)
    {
        *it = 'k';
    }
}