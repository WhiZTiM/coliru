#include <iostream>
#include <utility>
#include <tuple>

#include <cstdlib>

template< typename ...types >
void
ascendingPrint(types &&... _values)
{
    (std::cout << ... << std::forward< types >(_values)) << std::endl;
}

template< typename ...types, std::size_t ...indices >
void
descendingPrintHelper(std::tuple< types... > const & refs, std::index_sequence< indices... >)
{
    constexpr std::size_t back_index = sizeof...(indices) - 1;
    return ascendingPrint(std::forward< std::tuple_element_t< back_index - indices, std::tuple< types... > > >(std::get< back_index - indices >(refs))...);
}

template< typename ...types >
void
descendingPrint(types &&... _values)
{
    auto const refs = std::forward_as_tuple(std::forward< types >(_values)...);
    return descendingPrintHelper(refs, std::make_index_sequence< sizeof...(types) >{});
}

int
main()
{
    ascendingPrint(1, ' ', 2, ' ', 3);
    descendingPrint(1, ' ', 2, ' ', 3);
    return EXIT_SUCCESS;
}
