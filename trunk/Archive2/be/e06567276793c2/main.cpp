#include <iostream>
#include <iomanip>
#include <type_traits>
#include <utility>
#include <iterator>
#include <algorithm>
#include <vector>

#include <cstdlib>
#include <cassert>

template< typename first, typename second > 
void
sort_synchronously(first & f, second & s)
{
    std::size_t sz = f.size();
    assert(sz == s.size());
    struct P
    {
        typename first::iterator pfirst;
        typename second::iterator psecond;
        bool operator < (P const & p) const { return (*pfirst < *p.pfirst); }
        P(typename first::iterator pf, typename second::iterator ps)
            : pfirst(pf)
            , psecond(ps)
        { ; }
        P(P && p) { std::swap(pfirst, p.pfirst); std::swap(psecond, p.psecond); }
        void operator = (P && p) { std::swap(pfirst, p.pfirst); std::swap(psecond, p.psecond); }
    };
    std::vector< P > p;
    p.reserve(sz);
    auto fi = std::begin(f);
    auto si = std::begin(s);
    for (std::size_t i = 0; i < sz; ++i) {
        p.emplace_back(fi, si);
        ++fi;
        ++si;
    }
    std::sort(std::begin(p), std::end(p));
} 

int
main()
{
    std::vector< int > a{5, 4, 3, 2, 1};
    std::vector< int > b{1, 2, 3, 4, 5};
    std::copy(std::cbegin(a), std::cend(a), std::ostream_iterator< int >(std::cout, " ")); std::cout << std::endl;
    std::copy(std::cbegin(b), std::cend(b), std::ostream_iterator< int >(std::cout, " ")); std::cout << std::endl;
    sort_synchronously(a, b);
    std::copy(std::cbegin(a), std::cend(a), std::ostream_iterator< int >(std::cout, " ")); std::cout << std::endl;
    std::copy(std::cbegin(b), std::cend(b), std::ostream_iterator< int >(std::cout, " ")); std::cout << std::endl;
    return EXIT_SUCCESS;
}