// This code is released under the terms of the "CC0" license.  Full terms and conditions
// can be found at: http://creativecommons.org/publicdomain/zero/1.0/

#include <typeinfo>
#include <iostream>
#include <tuple>
#include <utility>
using namespace std;


template <char... chars>
using tstring = std::integer_sequence<char, chars...>;

template <typename T, T... chars>
constexpr tstring<chars...> operator""_tstr() { return { }; }

template <typename>
struct X;

template <char... elements>
struct X<tstring<elements...>> {
    static constexpr char str[sizeof...(elements) + 1] = { elements..., '\0' };

    const char* GetString() const { return str; }
};

using T = X<decltype("my_strddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddingmssssssssssssss"_tstr)>;

// test
int main()
{
    cout << T().str;
    return 0;
}
