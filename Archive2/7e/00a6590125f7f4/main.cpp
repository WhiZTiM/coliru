#define _HAS_ITERATOR_DEBUGGING 0
#define _SECURE_SCL 0

#include <boost/exception/detail/type_info.hpp>
#include <boost/range/algorithm_ext.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/range/numeric.hpp>
#include <boost/timer/timer.hpp>
#include <exception>
#include <iostream>
#include <iterator>
#include <vector>
#include <list>

#if defined(__GNUC__)
    #define NOINLINE __attribute__ ((noinline))
#elif defined(_MSC_VER)
    #define NOINLINE __declspec(noinline)
#else
    #define NOINLINE
#endif

template<int> NOINLINE void ASM_MARKER() { volatile int x = 0; (void)x; }

/******************************************************************************/
using namespace std;

template<typename Range>
void test(const Range &r)
{
    cout << boost::type_name<Range>() << ": ";

    boost::timer::auto_cpu_timer t;

    ASM_MARKER<111>();
    volatile int result = boost::accumulate(r, 0);
    ASM_MARKER<222>();

    (void)result;
}

int main() try
{
    vector<int> data(5000000);
    boost::iota(data, 0);
    boost::random_shuffle(data);

    list<int> l(begin(data), end(data));
    l.sort();

    auto v = data;
    boost::sort(v);

    vector<int*> vp;
    for(auto &x : data) vp.push_back(&x);
    boost::sort(vp, [](auto x, auto y){ return *x < *y; });

    for(unsigned i=0; i!=2; ++i)
    {
        test(v);
        test(l);
        test(vp | boost::adaptors::indirected);
    }
}
catch(const exception &e)
{
    cout << e.what() << endl;
}
