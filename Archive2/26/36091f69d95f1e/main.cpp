#include <iostream>
#include <stdexcept>
#include <iterator>
#include <type_traits>

#include <vector>

void DoThing(std::random_access_iterator_tag)
{
    std::cout << "A random access iterator\n";
}

void DoThing(std::input_iterator_tag)
{
    std::cout << "Not a random access iterator\n";
}

void DoThing(std::output_iterator_tag)
{
    std::cout << "An output iterator\n";
}

template<typename IterT>
void GoGoGo()
{
    typedef typename std::iterator_traits<IterT>::iterator_category category;
    DoThing(category{});
}

int main()
{
    GoGoGo<std::vector<uint8_t>::const_iterator>();
    GoGoGo<std::back_insert_iterator<std::vector<uint8_t>>>();
}