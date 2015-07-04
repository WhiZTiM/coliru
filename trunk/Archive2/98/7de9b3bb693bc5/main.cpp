#include <functional>
#include <set>
#include <string>
#include <unordered_map>
#include <map>
#include <iostream>

template < typename A, typename B >
    using wrapped_pair = std::pair< std::reference_wrapper<A>, std::reference_wrapper<B> > ;

struct cmp_wrapped_pair
{
    template < typename A, typename B > bool operator() ( const A& a, const B& b ) const
    {
        return a.first.get() < b.first.get() ||
               ( !( b.first.get() < a.first.get() ) && a.second.get() < b.second.get() ) ;
    }
};

template < typename MAP_TYPE >
auto sorted_snapshot_of( const MAP_TYPE& map ) // auto: function return type deduction is C++14
{
    using KEY = typename MAP_TYPE::key_type ;
    using VALUE = typename MAP_TYPE::mapped_type ;
    std::multiset< wrapped_pair< const VALUE, const KEY >, cmp_wrapped_pair > snapshot ;

    for( auto& pair : map ) snapshot.emplace( pair.second, pair.first ) ;
    return snapshot ;
}

int main()
{
    const std::unordered_map< std::string, int > unordered_map
    {
        { "zero", 0 }, { "one", 1 }, { "two", 2 }, { "three", 3 }, { "four", 4 },
        { "nihil", 0 }, { "unus", 1 }, { "duo", 2 }, { "tres", 3 }, { "quattuor", 4 },
        { "sunya", 0 }, { "eka", 1 }, { "dvi", 2 }, { "tri", 3 }, { "chatur", 4 }
    };

    // print a sorted (values, then keys) snapshot of the map
    for( const auto& pair : sorted_snapshot_of(unordered_map) )
        std::cout << pair.first.get() << " " << pair.second.get() << '\n' ;
}
