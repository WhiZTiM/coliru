#include <boost/range/algorithm.hpp>
#include <boost/range/adaptors.hpp>

using namespace boost::adaptors;

// only for succinct predicates without lambdas
#include <boost/phoenix.hpp>
using namespace boost::phoenix::arg_names;
using namespace std;
// for demo
#include <iostream>
#include <map>

int main()
{

   /* int myints[] = { 1,2,3,4,5 };
    std::vector<int> v (myints, myints + sizeof(myints) / sizeof(int) );
    boost::copy(
            v | filtered(arg1 % 2) | transformed(arg1 * arg1),
            std::ostream_iterator<double>(std::cout, "\n"));*/
    map<int,map<int,int> > test {1, {1,1}}
}
