#include <iostream>
#include <memory>
#include <utility>

struct foo
{
    template <typename U>
    void insert(std::unique_ptr<U> ptr)
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        this->insert(std::move(ptr));
    }
    
    template <typename U>
    void insert(U value) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    //    listAttrib.insert(value);
    }
};

int main()
{
    foo().insert(std::make_unique<int>(10));
}
