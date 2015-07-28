
#include<iostream>
#include<type_traits>
using namespace std;
int main() { 
    int i = 3;
    int &r = i;

    static_assert( is_same<decltype(i),int>::value, "");
    static_assert( is_same<decltype(r),int&>::value, "");

    cout << &i << endl;
    cout << &r << endl;
    auto lmb = [i,r]() { 
        static_assert( is_same<decltype(i),int >::value, "");
        static_assert( is_same<decltype(r),int&>::value, "Should be false, I feel"); // What?
        cout << &i << endl;                                                 
        cout << &r << endl;
    };
    lmb();
}
