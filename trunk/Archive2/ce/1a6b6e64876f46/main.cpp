#include <iostream>
#include <cstdlib>
#include <string>

enum counterSet{
    FIRST,
    SECOND
};

namespace detail{
    template <counterSet Set_>
    class count{
    public:
        template <typename Incremented_>
        static size_t increment(){
            static size_t c = counter++;
            return c;
        }
    private:
        static size_t counter;
    };
    template <counterSet Set_>
    size_t count<Set_>::counter = 0;
}

template <counterSet Set_, typename Member_>
class counter{
public:
    template <typename Incremented_>
    size_t incrementCounter(){return detail::count<Set_>::template increment<Incremented_>();}
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
        << foo1.incrementCounter<char>() << '\n'
        << foo1.incrementCounter<float>() << '\n'
        << foo1.incrementCounter<char>() << '\n'
        << foo2.incrementCounter<int>() << '\n';

}
