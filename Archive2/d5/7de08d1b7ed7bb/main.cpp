template<bool B>
struct stuff
{
    stuff<!B>& flip() & { return reinterpret_cast<stuff<!B>&>(*this); }
    stuff<!B> flip() && { return reinterpret_cast<stuff<!B>&>(*this); }
    
    explicit operator bool() const { return B; }
};

#include <iostream>

int main()
{
    if (auto s = stuff<true>{})
        std::cout << "normal\n";
    if (auto s = stuff<false>{}.flip())
        std::cout << "flipped\n";
}
