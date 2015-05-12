#include <iostream>
#include <cstdint>
#include <type_traits>

using namespace std;


int main()
{
    cout << "int == int32_t: " << is_same<int, int32_t>::value << endl;
    cout << "intptr_t == int32_t: " << is_same<intptr_t, int32_t>::value << endl;
    cout << "intptr_t == int64_t: " << is_same<intptr_t, int64_t>::value << endl;
    cout << "intptr_t == long: " << is_same<intptr_t, long>::value << endl;
    cout << "intptr_t == long long: " << is_same<intptr_t, long long>::value << endl;
}