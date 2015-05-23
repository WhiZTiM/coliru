template<bool B>
struct stuff
{
private:
    struct flip_proxy;
    
public:
    flip_proxy flip();
    
    explicit operator bool() const { return B; }
};

template<bool B>
struct stuff<B>::flip_proxy : stuff<B>
{
    template<class Base>
    flip_proxy(Base&& b) : stuff<B>(static_cast<Base&&>(b)) {}
    explicit operator bool() const { return !stuff<B>::operator bool(); }
};

template<bool B>
typename stuff<B>::flip_proxy stuff<B>::flip() { return *this; }

#include <iostream>

int main()
{
    if (auto s = stuff<true>{})
        std::cout << "normal\n";
    if (auto s = stuff<false>{}.flip())
        std::cout << "flipped\n";
}
