#include <string>
#include <iostream>
#include <type_traits>
using namespace std;

int main()
{
    int const  x = 50;
    int const& y = x;
    cout << std::is_const<std::remove_reference<int const>::type>::value << endl; // 1
    cout << std::is_const<std::remove_reference<int const&>::type>::value << endl; // 1
    
    return 0;
}