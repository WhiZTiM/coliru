#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

int main ()
{
    std::stringstream ss ("1 2 3 4");
    std::vector<int> {std::istream_iterator<int> {ss}, {}};
}