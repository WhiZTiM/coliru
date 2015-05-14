#include <iostream>
#include <boost/array.hpp>

int main()
{
    boost::array<int, 10> ar = {5,4,3,6,7,8,9,1,2,10};
    new (&ar) boost::array<int, 10>();
    std::cout << ar[0] << ',' << ar[1] << ',' << ar[2] << ',' << ar[3] << ',' << ar[4] << ',' << ar[5] << ',' << ar[6] << ',' << ar[7] << ',' << ar[8] << ',' << ar[9] << '\n';
}