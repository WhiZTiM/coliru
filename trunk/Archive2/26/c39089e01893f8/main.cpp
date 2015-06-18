#include <type_traits>
#include <iostream>

using namespace std;

int main() {
    cout << boolalpha << is_signed<decltype(declval<uint8_t>() & declval<int8_t>())>::value;
}