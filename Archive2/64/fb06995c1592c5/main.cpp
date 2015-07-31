#include <iostream>
#include <utility>
#include <random>
#include <algorithm>
#include <string>
#include <iterator>
#include <stdexcept>
#include <iomanip>

namespace game
{
    enum class suit { spades, hearts, diamonds, clubs } ;
    enum class rank { ace = 1, two, three, four, five, six, seven, eight, nine, ten, jack, queen, king } ;
    constexpr std::size_t CARDSET_SIZE = 52 ;

    struct card : std::pair<game::suit,game::rank>
    {
        using std::pair<game::suit,game::rank>::pair ;

        constexpr game::suit suit() const { return first ; }
        constexpr game::rank rank() const { return second ; }
    };

    std::string to_string( card c )
    {
        static const char suitc[] = "SHDC" ;
        static const char rankc[] = " A23456789XJQK" ;

        std::string str( 1, suitc[ int(c.suit()) ] ) ;

        if( c.rank() == rank::ten ) str += "10" ;
        else str += rankc[ int( c.rank() ) ] ;

        return str ;
    }

    std::ostream& operator<< ( std::ostream& stm, card c ) { return stm << to_string(c) ; }

    template < std::size_t N > struct bag_of_cards
    {
        bag_of_cards() = default ;

        template < typename CARD_ITERATOR > bag_of_cards( CARD_ITERATOR begin, CARD_ITERATOR end )
        {
            if( std::distance( begin, end ) > std::ptrdiff_t(N) ) throw std::out_of_range( "out of range" ) ;
            std::copy( begin, end, cards ) ;
        }
        card cards[N] ;
    };

    template < std::size_t N >
    std::ostream& operator<< ( std::ostream& stm, const bag_of_cards<N>& s )
    {
        for( card c : s.cards ) stm << std::setw(4) << c ;
        return stm ;
    }

    template < std::size_t N > void sort( bag_of_cards<N>& c )
    { std::sort( std::begin(c.cards), std::end(c.cards) ) ; }

    template < std::size_t N > using hand = bag_of_cards<N> ;

    struct pack : bag_of_cards<CARDSET_SIZE>
    {
        pack()
        {
            int s = int(suit::spades) ;
            int r = int(rank::ace) ;
            for( card& c : cards )
            {
                c = { suit(s), rank(r) } ;
                ++r ;
                if( r > int(rank::king) )
                {
                    r = int(rank::ace) ;
                    ++s ;
                }
            }
        }

        void shuffle()
        {
            static std::default_random_engine rng( std::random_device{}() ) ;
            std::shuffle( std::begin(cards), std::end(cards), rng ) ;
        }

        template < std::size_t N = 13 > hand<N> deal( std::size_t first ) const
        {
            if( (first+N) > CARDSET_SIZE ) throw std::out_of_range( "out of range" ) ;
            return { cards+first, cards+first+N } ;
        }
    };
}

int main()
{
    game::pack pack ;
	std::cout << pack << '\n' ; // ADL

	pack.shuffle() ;
	std::cout << '\n' << pack << "\n\n" ;

    for( std::size_t i = 0 ; i < 4 ; ++i )
    {
        auto hand = pack.deal<13>(i*13) ;
        sort(hand) ; // ADL
        static char player[] = "NESW" ;
        std::cout << player[i] << ":  " << hand << '\n' ;
    }
}
