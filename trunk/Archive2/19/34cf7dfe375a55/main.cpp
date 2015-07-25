#include <iostream> 
#include <random>

int main()
{
    constexpr std::size_t SZ = 10 ;
    char board[SZ][SZ] ;

    // fill with '.'
    // http://www.stroustrup.com/C++11FAQ.html#auto
    // http://www.stroustrup.com/C++11FAQ.html#for
    for( auto& row : board ) for( char& c : row ) c = '.' ;

    std::size_t required_cells = 15 ;
    std::size_t available_cells = SZ*SZ ;
    std::mt19937 rng( std::random_device {}( ) ) ;

    for( auto& row : board ) for( char& c : row ) // for each cell, one by one
    {
        if( required_cells > 0 ) // if there are more celles to be picked
        {
            // pick this cell with a probability of required_cells / available_cells  
            // ie. with our example of 100 cells, pick 15
            // pick board[0][0] with a probability opf 15/100
            // pick board[0][1] with a probability opf (15/100) * (14/99) + (85/100) * (15/99)
            //      ==   (15*14)/9900 + (85*15) / 9900  ==  1485/9900 == 15/100 
            // and so on.
            if( std::uniform_int_distribution<std::size_t>( 0, available_cells - 1 )( rng ) < required_cells )
            {
                c = '*' ;
                --required_cells ;
            }
            --available_cells ;
        }
    }

    // print the board
    for( const auto& row : board )
    {
        for( char c : row ) std::cout << c << ' ' ;
        std::cout << '\n' ;
    }
}
