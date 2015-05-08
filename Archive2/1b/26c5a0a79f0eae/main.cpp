#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

template <typename> class B;

template <typename T, class C> class A {};

template <typename T> class A<T, B<T>> {};

int main()
{
    return 0;
}