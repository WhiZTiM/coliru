#include <boost/timer/timer.hpp>
#include <iostream>

using namespace std;

auto inc = [](auto x) { return x + 1; };
auto zero = [](auto s) { return [](auto z) { return z; }; };
auto succ = [](auto n)
{
    return [=](auto s)
    {
        return [=](auto z)
        {
            return s(n(s)(z));
        };
    };
};

auto pow = [](auto b)
{
    return [=](auto e){ return e(b); };
};


auto bench = [](auto f)
{
    cout << "Timing: ";
    auto result = (boost::timer::auto_cpu_timer{},
                  f());
    cout << "Result: " << result << endl << endl;
};

int main()
{
    auto n0 = zero;
    auto n1 = succ(n0);
    auto n2 = succ(n1);
    auto n3 = succ(n2);
    auto n4 = succ(n3);
    auto n5 = succ(n4);
    auto n6 = succ(n5);
    auto n7 = succ(n6);
    auto n8 = succ(n7);
    auto n9 = succ(n8);
    
    bench([&]{ return succ(zero)(inc)(0); });
    bench([&]{ return succ(zero)(inc)(0); });
    
    bench([&]{ return succ(zero)(inc)(0); });

    bench([&]{ return pow(n2)(n3)(inc)(0); });

    bench([&]{ return pow(n9)(n9)(inc)(0); });
}
