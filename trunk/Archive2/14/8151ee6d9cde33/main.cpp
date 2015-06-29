#include <functional>
#include <iostream>
#include <utility>

using namespace std;

struct FF;

using any = function<FF(FF)>;

struct FF
{
    any f;

    template<typename F>
    FF(F x)
      : f(move(x))
    {}

    FF operator()(FF x) const
    {
        return f(move(x));
    }
};

/****************************************************************/

auto zero = [](auto) { return [](auto z) { return z; }; };

auto succ = [](auto n)
{
    return [n=move(n)](auto s)
    {
        return [=, s=move(s)](auto z)
        {
            return s(n(s)(move(z)));
        };
    };
};

any /* <--- erased type */ power = [](auto b)
{
    return [b=move(b)](const auto &e)
    {
        return e(b);
    };
};


template<unsigned N> auto n() { return succ(n<N-1>()); }
template<> auto n<0>() { return zero; }

int main()
{
    auto result = 0;
    auto action = [&](auto) { ++result; return zero; };

    any /* <--- erased type */ num = n<8>();
    power(num)(num)(action)(zero);

    cout << result << endl;
}
