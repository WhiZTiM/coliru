#include <functional>
#include <iostream>
using namespace std;

int main()
{
    function<int(int)> lambda = [&](auto x)
    {
        if(x == 0) return 1;
        else return x*lambda(x-1);
    };
    cout << lambda(5) << endl;
}