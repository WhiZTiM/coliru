#include <iostream>
using namespace std;

struct A
{
    const A& operator= (const A& other)
    {
        cout << __FUNCTION__ << "\n";
        return *this;
    }
};

int main()
{
     A a, b, c;
     (a = b) = c;
     return 0;
}
