//#include <initializer_list>
#include <iostream>

using namespace std;


template <typename T, unsigned N>
char (&ComputeArraySize(T (&)[N]))[N];

template <typename T, int SZ>
struct Arr
{
    typedef T Cont [SZ];
    
    Arr(const Cont &xx)
    {
        copy(xx, xx+SZ, m_arr);
    }
    
    void print() {
        for (auto x : m_arr)
            cout << x << " ";
        cout << endl;
    }
    
    Cont m_arr;
};


int main()
{
    Arr<int, 3> arr{{}};         //no fail :/
    Arr<int, 3> arr2{{1,2,3}};
    //Arr<int, 3> arr3{{1,2,3,4}}; //fails
    
    arr.print();
    arr2.print();
}
