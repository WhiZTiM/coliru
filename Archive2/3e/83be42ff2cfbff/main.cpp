#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <iostream>

int
main()
{
    int *p = new int(10);
    int *q = new int(20);

    boost::shared_ptr<int> ps(p);

    // This leads to a compiler error
    ps = boost::make_shared<int>(*q);

    std::cout << *p << std::endl;
    std::cout << *q << std::endl;
    return 0;
}
