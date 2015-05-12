#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <iterator>
#include <ext/functional>
#include <tr1/functional>
#include <boost/bind.hpp>

int g(int x, int y)
{
    return x + y;
}

int f(int x, int y)
{
    return x + y;
}

int main()
{
    int t[] = { 1, 2, 3, 4 };
    std::vector<int> input(t, t + 4);
    
    std::vector<double> results;
    
    const int arg = 1;
    const int C1 = 2;
    const int C2 = 3;
    
    std::transform(input.begin(), input.end(), std::back_inserter(results), std::bind2nd(std::ptr_fun(&g), C1));
        
    std::cout << f(g(arg, C1), C2) << std::endl;
    
    std::cout << __gnu_cxx::compose2(std::ptr_fun(&f)
                                   , std::bind2nd(std::ptr_fun(&g), C1)
                                   , __gnu_cxx::constant1<int>(C2)
                 )(arg) << std::endl;
    
    std::cout << std::tr1::bind(&f
                              , std::tr1::bind(&g
                                             , std::tr1::placeholders::_1
                                             , C1)
                              , C2
                 )(arg) << std::endl;
    
    std::cout << boost::bind(&f, boost::bind(&g, _1, C1), C2)(arg) << std::endl;
    
    boost::bind(&std::vector<double>::push_back
              , &results
              , boost::bind(&g, _1, C1)
              )(arg);
    std::cout << results.back() << std::endl;              
}
