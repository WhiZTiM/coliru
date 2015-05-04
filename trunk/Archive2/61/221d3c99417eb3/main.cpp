template <class T>
class Derived;

typedef Derived<int> _Int;

class Base
{
    // ...
    virtual _Int Foo() = 0;
};

template<typename T>
class Derived
    : public Base
{
public:
    // ...
    _Int Foo() override
    {
        return _Int();
    }
};


int main()
{
    _Int x;
    x.Foo();
}