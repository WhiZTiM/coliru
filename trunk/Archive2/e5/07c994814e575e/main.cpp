#include <iostream>
#include <string>
#include <vector>

class Foo{
public:
    Foo(int value = 0) : val_{value}{
        std::cout << "Foo being constructed with value of " << val_ << "\n";
    }
    Foo(const Foo &other) : val_{other.val_}{
        std::cout << "Foo being copy constructed with value of " << val_ << "\n";
    }
    Foo(const Foo &&other) : val_{std::move(other.val_)}{ // not really anything to do here, because Foo is pretty trivial.
        std::cout << "Foo being move constructed with value of " << val_ << "\n";
    }
    Foo &operator=(const Foo &other){
        val_ = other.val_; std::cout << "Foo value copied! Value now " << val_ << "\n";
        return *this;
    }
    const int& getValue(){return val_;}
private:
    int
        val_;
};

Foo getFooFromVector(const std::vector<Foo> &vectorOfFoos, size_t location){
    Foo const
        *locationPointer = &vectorOfFoos[location];
    return *locationPointer;
}

int main()
{
    std::vector<Foo>
        myVector{Foo{0}, Foo{1}, Foo{2}, Foo{3}, Foo{4}};
    Foo 
        myFoo = getFooFromVector(myVector, 1);
    std::cout << "MyFoo value: " << myFoo.getValue() << "\n";
}
