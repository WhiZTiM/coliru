#include <iostream>
#include <cstdlib>
#include <string>

enum counterSet{
    FIRST,
    SECOND
};

namespace detail{
    template <counterSet Set_, typename Incremented_>
    size_t counterIncrementer(){
        static size_t count = 0;
        return ++count;
    }
}

template <counterSet Set_, typename Member_>
class counter{
public:
    template <typename Incremented_>
    size_t incrementCounter(){return detail::counterIncrementer<Set_, Incremented_>();}
};

template <counterSet Set_>
class Foo : public counter<Set_, Foo<Set_>> {
};

int main()
{
    Foo<FIRST>
        foo1;
    Foo<SECOND>
        foo2;
        
    foo1.incrementCounter<int>();
    std::cout 
        << foo1.incrementCounter<int>() << '\n'
        << foo2.incrementCounter<int>() << '\n';

}
