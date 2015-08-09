#include <iostream>
#include <initializer_list>
#include <memory>
#include <vector>

class Base {
public:
    virtual void identity() const
    {
        std::cout << "Base\n";
    }

    virtual ~Base() = default;
};

class Derived: public Base {
public:
    virtual void identity() const override
    {
        std::cout << "Derived\n";
    }
};

void func ( std::initializer_list<std::reference_wrapper<Base>> objects )
{
    std::vector<std::reference_wrapper<Base>> bases;

    for ( auto& i : objects ) {
        bases.emplace_back ( i );
    }

    for ( auto& i : bases ) {
        i.get().identity();
    }
}

int main()
{
    Base i1, i3;
    Derived i2;
    // func ( {std::ref(i1), std::ref(i2), std::ref(i3)} );
    func ( { i1, i2, i3 } ); // implicit conversion from derived& to base&
}