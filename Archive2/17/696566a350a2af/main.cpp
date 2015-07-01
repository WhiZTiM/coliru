#include <iostream>
using namespace std;

namespace B
{
    template <typename T>
    void func()
    {
        cout << "Primary" << endl;
    }
    
    template <> void func<int>();
}

namespace A
{
    template <> void B::func<int>() {cout <<"int spec"<<endl;}
}

int main()
{
    B::func<double>();
    B::func<int>();
    return 0;
}