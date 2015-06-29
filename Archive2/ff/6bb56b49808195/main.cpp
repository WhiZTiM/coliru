#include <list>
#include <vector>
#include <iostream>

#include <boost/utility.hpp>

int main()
{
    std::list<int> ints {1,2,3,4,5,6,7};
    
    // begin/end OK with boost::next or std::next
    std::cout << *(std::next(begin(ints), 2)) << std::endl;
    std::cout << *(std::next(end(ints), -2)) << std::endl;

    std::cout << *(boost::next(begin(ints), 2)) << std::endl;
    std::cout << *(boost::next(end(ints), -2)) << std::endl;


    // rbegin/rend KO with boost::next
    std::cout << *(std::next(rbegin(ints), 2)) << std::endl;
    std::cout << *(std::next(rend(ints), -2)) << std::endl;

    std::cout << *(boost::next(rbegin(ints), 2)) << std::endl;
    std::cout << *(boost::next(rend(ints), -2)) << std::endl;
}
