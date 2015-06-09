#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

namespace helpers
{
    template<class Iterator>
    Iterator deleteNonUnique(Iterator first, Iterator last)
    {
        while (first != last)
        {
            Iterator next(first);
            last = std::remove(++next, last, *first);
            first = next;
        }
        return last;
    }
}

int main()
{
    int a[12] = {3,2,2,3,4,6,1,3,2,4,0,1};
    std::vector<int> v(a, a + sizeof a / sizeof a[0]);
    std::copy (v.begin(), v.end(), std::ostream_iterator<int>(std::cout, ", "));
    std::cout << std:: endl << "size: " << v.size();
       
    std::cout << std::endl;
    v.erase(helpers::deleteNonUnique(v.begin(), v.end()), v.end());
    std::copy (v.begin(), v.end(), std::ostream_iterator<int>(std::cout, ", "));
    std::cout << std::endl << v.size();
}
