template<typename T> class bar;

namespace NS
{
    template<typename T>
    class foo
    {
        foo() {}

        template<typename U> friend class bar;
    };
}

template<typename R>
class bar
{
public:
    bar()
    {
        NS::foo<int> f;
    }
};


int main(int, char **)
{
    bar<int> b;
    
    return 0;
}
