#include <iostream>
#include <sstream>
#include <time.h>
#include <string>
#include <math.h>
#include <boost/type_index.hpp>

int main (void)
{ 
    int a[] = { 1, 3};
    std::cerr << boost::typeindex::type_id_with_cvr< decltype(sqrt(a[0]*a[0]))>().pretty_name() << std::endl;
}