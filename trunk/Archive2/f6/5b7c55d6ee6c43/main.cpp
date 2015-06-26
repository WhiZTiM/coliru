#include <boost/fusion/container.hpp>
#include <boost/fusion/algorithm.hpp>
#include <iostream>

int main()
{
    using namespace std;
    using namespace boost;
    
    double x = 0.5;
    int y = 11;
    char z = 'a';
    
    auto closures = fusion::make_vector
    (
        [&]{ return x; },
        [&]{ return y; },
        [&]{ return z; }
    );
    
    fusion::for_each(closures, [](auto a)
    {
        cout << a() << endl;
    });
    
    fusion::for_each(push_back(closures, [&]{ return x + y; }), [](auto a)
    {
        cout << a() << endl;
    });
}

