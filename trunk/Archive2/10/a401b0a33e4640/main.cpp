#include <boost/math/distributions.hpp>
#include <boost/function.hpp>
#include <boost/random.hpp>
#include <random>

static boost::mt19937 gen;
typedef boost::function<double()> Distri;

Distri new_func()
{
    std::uniform_real_distribution<> Uni(1,2);
    return boost::variate_generator< boost::mt19937, std::uniform_real_distribution<>>(gen , Uni);
}

int main ()
{
    std::vector<double> test;
    //something like
    Distri d = new_func();

    // generate 100 new elements:
    std::generate_n(back_inserter(test), 100, d);

    // overwrite existing elements:
    std::for_each(test.begin(), test.end(), [&](double& v) { v = d(); }); // overwriting
}
