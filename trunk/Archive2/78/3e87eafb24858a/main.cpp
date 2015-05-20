#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <string>
#include <map>
#include <iostream>

typedef boost::function<bool (std::string::const_iterator& pos)> opcodeFunc;


bool getStatic(std::string::const_iterator& pos)
{

    pos++;

    return true;
}

int main()
{
    
    std::string bla = "bla";
    std::string::const_iterator pos = bla.begin();

    opcodeFunc f= boost::bind(getStatic,_1);

    f(pos);
    
    std::cout << *pos << std::endl;
}
