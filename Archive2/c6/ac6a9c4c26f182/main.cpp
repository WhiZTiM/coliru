#include <iostream>
#include <vector>
#include <boost/iterator/counting_iterator.hpp>

int main()
{    
    auto makeNumbersVector = [] (const short FirstRef, const short LastRef)
    {
        return std::vector<short>(boost::counting_iterator<short>(FirstRef),
                                  boost::counting_iterator<short>(LastRef));
    };
    
    auto showNumbers = [] (const std::vector<short> numbers)  
    {  
        for (auto number : numbers)  
            std::cout << number << ' ';
    };
    
    showNumbers(makeNumbersVector(0, 10));
}
