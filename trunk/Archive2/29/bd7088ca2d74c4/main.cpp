#include <list>
#include <utility>
#include <scoped_allocator>
#include <boost/pool/pool_alloc.hpp>

int main()
{
    typedef std::pair<int, int> Pair;
    std::list<Pair, std::scoped_allocator_adaptor<boost::fast_pool_allocator<Pair>>> list;

    list.emplace(list.begin(), 1, 2);
}