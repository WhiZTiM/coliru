#include <array>
#include <queue>
#include <memory>
#include <type_traits>
#include <iostream>
#include <iomanip>

using byte = unsigned char ;
using byte4 = unsigned char[4] ;

template< typename T > std::array< byte, sizeof(T) >  to_bytes( const T& object )
{
    std::array< byte, sizeof(T) > bytes ;

    const byte* begin = reinterpret_cast< const byte* >( std::addressof(object) ) ;
    const byte* end = begin + sizeof(T) ;
    std::copy( begin, end, std::begin(bytes) ) ;

    return bytes ;
}

template< typename T >
T& from_bytes( const std::array< byte, sizeof(T) >& bytes, T& object )
{
    // http://en.cppreference.com/w/cpp/types/is_trivially_copyable
    static_assert( std::is_trivially_copyable<T>::value, "not a TriviallyCopyable type" ) ;

    byte* begin_object = reinterpret_cast< byte* >( std::addressof(object) ) ;
    std::copy( std::begin(bytes), std::end(bytes), begin_object ) ;

    return object ;
}

int main()
{
    double d = 123.456789 ;
    const auto bytes = to_bytes(d) ;

    std::cout << std::hex << std::setfill('0') ;
    for( byte b : bytes ) std::cout << std::setw(2) << int(b) << ' ' ;
    std::cout << '\n' ;

    d = 0 ;
    from_bytes( bytes, d ) ;
    std::cout << std::fixed << d << '\n' ;

    int p = 512;
    byte4 a;
    
    memcpy(&a,&p,sizeof(a));
    /*
    a[0] = p & 0xff;
    a[1] = (p >> 8)  & 0xff;
    a[2] = (p >> 16) & 0xff;
    a[3] = (p >> 24) & 0xff;
    */
    std::cout << std::dec << int(a[0])<< int(a[1])<< int(a[2])<< int(a[3])<<'\n'; 
    
    std::cout << std::setw(sizeof(a)) <<std::hex << int(*a) << '\n' <<std::hex << p << '\n';
    
    

    //int arr[] = { 1, 63, 256, 511, 1024 } ;
    enum CHANNEL {MONO=1,STEREO};
    CHANNEL c = CHANNEL::STEREO;
    int z = 255;
    bool bb = false;
    unsigned char arr[]= {0x7f,'B',static_cast<byte>(z), bb, static_cast<byte>(c)};
    const auto array_bytes = to_bytes(arr) ;
    
   
    for( byte b : array_bytes ) std::cout << std::setw(2) << int(b) << ' ' ;
    std::cout << '\n' ;
    
    for( byte& v : arr ) v = -1 ;
    from_bytes( array_bytes, arr ) ;
    
    std::cout << '\n' ;
}
