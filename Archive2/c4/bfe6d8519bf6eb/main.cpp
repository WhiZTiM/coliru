#include <iostream>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/contains.hpp>

typedef boost::mpl::vector<int, void, float> sexy_types;

template <typename T>
void SexyMethod(T sexyParameter)
{   
    static_assert(boost::mpl::contains<sexy_types, T>::value, "This method takes sexy parameters only.");
}

int main() 
{
    SexyMethod(5);
    SexyMethod("hi");
}