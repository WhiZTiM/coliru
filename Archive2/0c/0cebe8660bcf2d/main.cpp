#include <string>
#include <type_traits>
#include <iostream>
using namespace std;

template<class T>
class Deducer;

template <class T>
void deducer(T t)
{
   Deducer<T> type;
   Deducer<decltype(type)> paramType;

}

template <class T>
struct is_const_ref
{
     static constexpr int value = std::is_same<T, const T&>::value;
};


     

int main() {
int const  x = 50;
int const& y = x;

cout << is_const_ref<decltype(x)>::value << endl;
cout << is_const_ref<decltype(y)>::value << endl;

}
