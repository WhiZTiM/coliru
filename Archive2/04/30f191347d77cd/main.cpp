#include <array>
#include <utility>
#include <stdexcept>
#include <cassert>

struct uuid {
    std::array< uint8_t, 4 > low;
    std::array< uint8_t, 2 > mid;
    std::array< uint8_t, 2 > high;
    std::array< uint8_t, 2 > clock;
    std::array< uint8_t, 6 > node;
    int version;
    int variant;
};

constexpr int decode_hex_char( char c ) {
    if ( c >= '0' && c <= '9' ) return c - '0';
    if ( c >= 'a' && c <= 'f' ) return c - 'a';
    if ( c >= 'A' && c <= 'F' ) return c - 'A';
    throw std::out_of_range{ "invalid hex digit" };
}

template< typename rai, std::size_t ... x >
constexpr
std::array< std::uint8_t, sizeof ... (x) >
decode_hex_sequence( rai i, std::index_sequence< x ... > ) {
    return {{ static_cast< std::uint8_t >( decode_hex_char( i[ x * 2 ] ) + decode_hex_char( i[ x * 2 + 1 ] ) * 16 ) ... }};
}

constexpr uuid operator "" _uuid( char const * s, std::size_t l ) {
    assert ( l == 36 );
    assert ( s[ 8 ] == '-' );
    assert ( s[ 8+1+4 ] == '-' );
    assert ( s[ 8+1+4+1+4 ] == '-' );
    assert ( s[ 8+1+4+1+4+1+4 ] == '-' );
    
    return {
        decode_hex_sequence( s, std::make_index_sequence< 4 >{} ),
        decode_hex_sequence( s + 8+1, std::make_index_sequence< 2 >{} ),
        decode_hex_sequence( s + 8+1+4+1, std::make_index_sequence< 2 >{} ),
        decode_hex_sequence( s + 8+1+4+1+4+1, std::make_index_sequence< 2 >{} ),
        decode_hex_sequence( s + 8+1+4+1+4+1+4+1, std::make_index_sequence< 6 >{} ),
        decode_hex_char( s[ 8+1+4+1 ] ),
        decode_hex_char( s[ 8+1+4+1+4+1 ] ) / 4
    };
}

constexpr uuid x = "123e4567-e89b-12d3-a456-426655440000"_uuid;
