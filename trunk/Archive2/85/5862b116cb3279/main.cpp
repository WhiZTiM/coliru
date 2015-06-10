#include <boost/asio/coroutine.hpp>
#include <iostream>

using namespace std;
using namespace boost;

#include <boost/asio/yield.hpp>

#define await(wanted, future) \
yield future([self = coroutine(*this)](auto x) mutable \
{ \
    auto copy = self; \
    copy.wanted = x; \
    copy(); \
}) \
/**/

auto foo = [](auto continuation) // .then
{
    continuation(1);
    continuation(2);
    continuation(3);
};

auto bar = [](auto continuation) // .then
{
    continuation('a');
    continuation('b');
    continuation('c');
};

struct coroutine : asio::coroutine
{
    int x;
    char y;
    void operator()()
    {
        reenter(*this)
        {
            await(x, foo); // x = await foo;
            await(y, bar); // y = await bar;
            cout << x << " " << y << endl;
        }
    };
};

int main()
{
    coroutine{}();
}
