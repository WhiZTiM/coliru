#include<iostream>
using namespace std;

template <typename T>
class MyClass
{
    public:
    MyClass()
    {
        cout << "Nothing to see here. Just a regular T." << endl;
    }
};

template <typename T, int N>
class MyClass<T[N]>
{
    public:
    MyClass()
    {
        cout << "Creating MyClass templated on an array of size " << N << endl;
    }
};

int main()
{
    MyClass <int> {};
    MyClass <int[10]> {};
    return 0;
}