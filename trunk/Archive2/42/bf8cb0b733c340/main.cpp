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
    
    // Optionally
    //constexpr static const char str[sizeof...(elements) + 1] = { elements..., '\0' };
    
    constexpr static const char* GetString() { return { elements..., '\0' }; }
};

using T = X<decltype("my_string"_tstr)>;
using T2 = X<decltype("my_strinh"_tstr)>;

// test
int main()
{
    T t;
    cout << sizeof(T) << endl;
    cout << typeid(T).name() << endl;
    cout << typeid(T2).name() << endl;
	return 0;
}
