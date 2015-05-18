#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/variate_generator.hpp>

boost::mt19937 gen;

template <typename T> T func() {
    std::uniform_real_distribution<> uni(1, 2);
    boost::variate_generator<boost::mt19937&, std::uniform_real_distribution<> > uniform(gen, uni);
    return uniform();
}

int main()
{
    std::vector<double> test(10);
    for(int i = 0; i < test.size(); ++i)    
        test[i] = func<double>();
    for(auto c : test)
        std::cout << c << " " ;
    return 0;
}