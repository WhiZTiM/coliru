//http://stackoverflow.com/questions/6622452/alias-template-specialisation
#include <iostream>
#include <type_traits>

class A;
class B;

template<class T>
class C
{
    public:
        template<class Q = T>
        typename std::enable_if<std::is_same<Q, B>::value, bool>::type
        c()
        {
            return true;
        }

        template<class Q = T>
        typename std::enable_if<!std::is_same<Q, B>::value, bool>::type
        c()
        {
            return false;
        }
};

int main() {
    C<A> ca;
    C<B> cb;
    if (!ca.c() && cb.c())
        std::cout << "It works!" << std::endl;
    return 0;
}
