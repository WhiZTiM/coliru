/**
 *  verbalsaint
 */

#include <iostream>
#include <functional>

using namespace std;

int main()
{

    auto plus_2 = [](auto&& x)
    {
        return [&x](auto&& y) -> long long
        {
            return x() + y();
        };
    };

    function<function<long long(void)>(int)> fib = [&fib, &plus_2](int x)
    {
        return [=]() -> long long
        {
            long long very_big_array[100000]; // tail call opted.

            if (x == 0 || x == 1){
                return 1;
            }

            return plus_2(fib(x-1))(fib(x-2));
        };
    };

    auto calculate_fib = [&fib](auto N)
    {
        return fib(N)();
    };

    cout << calculate_fib(30) <<endl;
}
