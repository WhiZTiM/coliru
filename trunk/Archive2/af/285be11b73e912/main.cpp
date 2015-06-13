#include <iostream>

template<int M, class Pred>
constexpr auto fun(Pred pred)
{
    return pred(1) <= M;
}

template<int M>
struct C
{
        template<int N>
        static constexpr auto pred(int x) noexcept
        {
            // simulate a constexpr lambda (not allowed in C++14)
            struct lambda
            {
                    int n_, x_;
                    
                    constexpr auto operator()(int y) const noexcept
                    {
                            return this->n_ * this->x_ + y;
                    }
            };

            return fun<M>(lambda{N, x});
        }
};

int main()
{
    constexpr auto res = C<7>::template pred<2>(3);
    std::cout << res; // prints 1, since 2 * 3 + 1 <= 7;
}
