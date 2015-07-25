#include <iostream> 
#include <numeric>
#include <iterator>
#include <algorithm>
#include <random>

int main()
{
    constexpr std::size_t SZ = 10 ;
    char board[SZ][SZ] ;

    // fill with '.'
    // http://www.stroustrup.com/C++11FAQ.html#auto
    // http://www.stroustrup.com/C++11FAQ.html#for
    for( auto& row : board ) for( char& c : row ) c = '.' ;

    std::size_t REQUIRED_CELLS = 15 ;

    // fill up an array with positions 0 .. SZ*SZ-1
    std::size_t positions[SZ*SZ] ;
    // http://en.cppreference.com/w/cpp/algorithm/iota
    // http://en.cppreference.com/w/cpp/iterator/begin
    std::iota( std::begin(positions), std::end(positions), 0 ) ;

    // shuffle it randomly
    // http://en.cppreference.com/w/cpp/algorithm/random_shuffle
    // http://en.cppreference.com/w/cpp/numeric/random
    std::shuffle( std::begin(positions), std::end(positions),
                  std::mt19937( std::random_device {}() ) ) ;

    // pick the first REQUIRED_CELLS positions in the shiffled sequence
    for( std::size_t i = 0 ; i < REQUIRED_CELLS ; ++i )
    {
        board[0][ positions[i] ] = '*' ;

        // or, in long hand:
        /*
        const auto pos = positions[i] ;
        const auto row = pos / SZ ;
        const auto col = pos % SZ ;
        board[row][col] = '*' ;
        */
    }

    // print the board
    for( const auto& row : board )
    {
        for( char c : row ) std::cout << c << ' ' ;
        std::cout << '\n' ;
    }
}
