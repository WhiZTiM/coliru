#include <iostream>
#include <string>
#include <type_traits>

using namespace std;

template<class ...> using void_t = void;

template< class, class = void >
struct is_special : public std::false_type {};

template< class T >
struct is_special<T, void_t<decltype(T::is_special)> > : public std::true_type {};


template <class A, class B, typename = std::enable_if_t<!is_special<A>::value> >
void foo(A& a, B& b)
{
    cout << "generic fallback" << endl;
}

template <class A, class B, typename = std::enable_if_t<is_special<A>::value> >
auto foo(A& a, B& b)
{
    cout << "specialized fallback" << endl;
}


template <class A, typename = std::enable_if_t<!is_special<A>::value>>
void foo(A& a, int &i)
{
    cout << "generic int" << endl;
}

template <class A, typename = std::enable_if_t<!is_special<A>::value>>
void foo(A& a, string& s)
{
    cout << "generic str" << endl;
}

struct mine
{
    int is_special;
};


int main()
{
int x;
string y;
float z;
string generic;
mine special;

foo(generic, x); // generic int
foo(generic, y); // generic string
foo(generic, z); // generic fallback
foo(special, x); // specialized fallback
foo(special, y); // specialized fallback
foo(special, z); // specialized fallback

return 0;
}