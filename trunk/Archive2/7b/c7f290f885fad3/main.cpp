#include <boost/asio/coroutine.hpp>
#include <iostream>

using namespace std;
using namespace boost;

#include <boost/asio/yield.hpp>

struct first_coroutine : asio::coroutine
{
    unsigned i;

    int operator()()
    {
        reenter(*this)
        {
            for(i = 0; ; ++i)
                yield return i;
        }
    };
};

struct second_coroutine : asio::coroutine
{
    first_coroutine inner;

    int operator()()
    {
        reenter(*this)
        {
            while(true)
                yield return inner() * 2;
        }
    };
};

int main()
{
    second_coroutine c;
    for(int i=0; i!=5; ++i)
        cout << c() << endl;
}
