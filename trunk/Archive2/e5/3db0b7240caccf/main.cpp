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
        cout << "XX sz " << sizeof ComputeArraySize(xx) << endl;
        copy(xx, xx+SZ, m_arr);
    }
    
    Cont m_arr;
};


int main()
{
    int x[] = {1,2,3};
    Arr<int, 3> arr{{}};
    
    for (auto x : arr.m_arr)
        cout << x << ",";
        
    cout << endl;
    
    cout << sizeof ComputeArraySize(x) << endl;
    static_assert(sizeof ComputeArraySize(x) == 3, "does not match");

}
