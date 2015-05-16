#include <iostream>
#include <memory>
#include <array>
#include <vector>
#include <iterator>

struct block
{
    virtual ~block() = default ;
    // ...
    const int block_number = ++slno ;
    static int slno ;
};

int block::slno = 0 ;

struct tetrimino
{
    // transfer of ownership is required for std::unique_ptr<block>
    std::array< std::unique_ptr<block>, 4 > blocks ;

    tetrimino() { new_blocks() ; }

    // give it four new blocks
    void new_blocks()
    {
        // note: std::make_unique<> requires C++14
        // http://en.cppreference.com/w/cpp/memory/unique_ptr/make_unique
        // with C++11, ptr = std::unique_ptr<block>( new block( /* ... */ ) ) ;
        for( auto& ptr : blocks ) ptr = std::make_unique<block>( /* ... */ ) ;
    }

    void cycle_blocks( std::vector< std::unique_ptr<block> >& pile )
    {
        // transfer ownership of the blocks to pile (move the smart pointers into the pile)
        // see: http://en.cppreference.com/w/cpp/iterator/move_iterator
        // http://en.cppreference.com/w/cpp/iterator/make_move_iterator
        pile.insert( std::end(pile),
                     std::make_move_iterator( std::begin(blocks) ),
                     std::make_move_iterator( std::end(blocks) ) ) ;

        print( std::cout << "after move, " ) << '\n' ;

        new_blocks() ; // give it four new blocks
        print( std::cout << "after new_blocks(), " ) << '\n' ;
    }

    std::ostream& print( std::ostream& stm ) const
    {
        stm << "tetrimino holds blocks: " ;
        for( const auto& ptr : blocks )
            if(ptr) stm << ptr->block_number << ' ' ;
            else stm << "nil " ;
        return stm ;
    }
};

std::ostream& operator<< ( std::ostream& stm, const tetrimino& tet ) { return tet.print(stm) ; }

int main()
{
    tetrimino tet ;
    std::cout << tet << '\n' ;
    std::vector< std::unique_ptr<block> > pile ;

    for( int i = 0 ; i < 3 ; ++i )
    {
        tet.cycle_blocks(pile) ;

        std::cout << "pile now holds blocks: " ;
        for( const auto& ptr : pile ) std::cout << ptr->block_number << ' ' ;
        std::cout << "\n---------------------------\n" ;
    }
}
