#include <iterator>
#include <type_traits>


#include <vector>

template<typename RandomAccessIter>
void func(RandomAccessIter& iter)
{
    typedef typename std::iterator_traits<RandomAccessIter>::iterator_category iter_cateygory_t;
    
    static_assert(std::is_base_of<iter_cateygory_t, std::random_access_iterator_tag>::value, "Not the fucking same.");
}

int main()
{
    std::vector<int> payload;
    
    std::vector<int>::iterator begin = std::begin(payload);
    
    func(begin);
}