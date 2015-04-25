#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

std::set< std::vector<int> > unique_n_combinations( std::vector<int> seq, std::size_t n = 3 )
{
    std::set< std::vector<int> > n_tuples ;
    if( seq.size() >= n ) do
    {
        std::vector<int> temp( seq.begin(), seq.begin() + n );
        std::sort( temp.begin(), temp.end() ) ;
        n_tuples.insert( std::move(temp) ) ;
    }
    while( std::next_permutation( seq.begin(), seq.end() ) ) ;

    return n_tuples ;
}

void print_unique_n_combinations( std::vector<int> seq, std::size_t n = 3 )
{
    std::sort( seq.begin(), seq.end() ) ;
    seq.erase( std::unique( seq.begin(), seq.end() ), seq.end() ) ;
    for( const auto& n_tuple : unique_n_combinations( seq, n ) )
    {
        for( int v : n_tuple ) std::cout << v << ' ' ;
        std::cout << '\n' ;
    }
    std::cout << "-----------------------------\n" ;
}

int main()
{
    print_unique_n_combinations( { 0, 1, 2, 3 }, 3 ) ;
    print_unique_n_combinations( { 0, 1, 2, 3, 4, 5, 6 }, 4 ) ;
}
