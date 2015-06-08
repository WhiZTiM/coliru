#include <iostream>
#include <sstream>
#include <time.h>
#include <string>
#include <math.h>
#include <boost/type_index.hpp>

int main (void)
{ 
    std::cerr << boost::typeindex::type_id_with_cvr< decltype(sqrt(1.2*1))>().pretty_name() << std::endl;
}