#include <iostream>
#include <string>
#include <fstream>
#include <deque>
#include <algorithm>
#include <vector>
#include <iterator>

struct circular_buffer
{
    explicit circular_buffer( std::size_t buffsz = 500 ) : sz(buffsz) {}

    void push( std::string&& line )
    {
        buffer.push_front( std::move(line) ) ;
        static const std::size_t max_cache_size = std::max( sz, std::size_t(1000) ) ;
        if( buffer.size() > max_cache_size ) buffer.resize(sz) ;
    }

    std::vector<std::string> move_lines()
    {
        if( buffer.size() > sz ) buffer.resize(sz) ;
        return { std::make_move_iterator( buffer.rbegin() ), std::make_move_iterator( buffer.rend() ) } ;
    }

    std::size_t sz ;
    std::deque<std::string> buffer ;
};

std::vector<std::string> get_last_n_lines( std::ifstream file, std::size_t n )
{
    circular_buffer buffer(n) ;
    std::string line ;
    while( std::getline( file, line ) ) buffer.push( std::move(line) ) ;
    return buffer.move_lines() ;
}

int main()
{
    for( std::string line : get_last_n_lines( std::ifstream( __FILE__ ), 10  ) ) std::cout << line << '\n' ;
}
// **** last line ****
