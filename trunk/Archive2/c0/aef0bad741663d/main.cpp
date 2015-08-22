#include <iostream>
using namespace std;

template<class F>
struct wrapper
{
    static_assert(std::is_empty<F>(), "Lambdas must be empty");
    template<class... Ts>
    constexpr decltype(auto) operator()(Ts&&... xs) const
    {
        return reinterpret_cast<const F&>(*this)(std::forward<Ts>(xs)...);
    }
};


struct wrapper_factor
{
    template<class F>
    constexpr wrapper<F> operator += (F*)
    {
        return {};
    }
};

struct addr_add
{
    template<class T>
    friend typename std::remove_reference<T>::type *operator+(addr_add, T &&t) 
    {
        return &t;
    }
};

#define STATIC_LAMBDA wrapper_factor() += true ? nullptr : addr_add() + []

const constexpr auto add_one = STATIC_LAMBDA(auto x)
{
    return x + 1;
};

constexpr int increment(int var) {
    return add_one(var);
}

int main()
{

    std::cout << add_one(42);


    return 0; 
}