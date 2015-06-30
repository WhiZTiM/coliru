#include <iostream>

inline std::size_t strlen( const char* p ) // invariant p != nullptr
{
    std::size_t n = 0 ;
    while( *p++ != 0 ) ++n ;
    return n ;
}

template < typename SRCE_ITERATOR, typename DEST_ITERATOR >
void copy( SRCE_ITERATOR begin, SRCE_ITERATOR end, DEST_ITERATOR dest )
{ while( begin != end ) *dest++ = *begin++ ; }

template < typename ITERATOR_A, typename ITERATOR_B >
bool equal( ITERATOR_A beg_a, ITERATOR_A end_a, ITERATOR_B beg_b, ITERATOR_B end_b )
{
    for( ; beg_a != end_a && beg_b != end_b ; ++beg_a, ++beg_b )
        if( ! ( *beg_a == *beg_b ) ) return false ;
    return beg_a == end_a && beg_b == end_b ; // reached end of both sequences
}

template < typename ITERATOR_A, typename ITERATOR_B >
bool lex_less( ITERATOR_A beg_a, ITERATOR_A end_a, ITERATOR_B beg_b, ITERATOR_B end_b )
{
    for( ; beg_a != end_a && beg_b != end_b ; ++beg_a, ++beg_b )
        if( *beg_a < *beg_b ) return true ;
        else if ( *beg_b < *beg_a ) return false ;
    return beg_a == end_a && beg_b != end_b ; // reached end of a, but did not reach end of b
}

[[ noreturn ]] [[ deprecated( "instead, use the assert in <cassert>" ) ]]
inline bool my_assert_( const char* text, const char* source_file, unsigned int line )
{
   std::cerr <<  "\n\nassertion '" << text << "' failed\n    file: "
             << source_file << " line: " << line << '\n' ;

   // crude workaround to call std::abort() without explicitly including the header
   struct assertion_failure {}; throw assertion_failure {} ;
   // note: without a handler, default behaviour is:
   // std::terminate() => std::terminate_handler => std::abort()
}

#ifdef NDEBUG
    #define my_assert(e) static_cast< const void >(0)
#else
    #define my_assert(e) static_cast< const void >\
        ( ( (!!(e)) || my_assert_( #e, __FILE__, __LINE__ ) ), 0 )
#endif // NDEBUG

class String {

    std::size_t size ;
    char * buffer ;


    public:
        String() : size(0), buffer( new char[0] ) {}

        String( const String& that ) : size(that.size), buffer( new char[size]{} )
        { copy( that.buffer, that.buffer+size, buffer ) ; }

        String( const char* cstr ) : size( strlen(cstr) ), buffer( new char[size]{} )
        { copy( cstr, cstr+size, buffer ) ; }

        // an extra constructor: helper to make operator+= exception safe
        String( std::size_t len ) : size(len), buffer( new char[size]{} ) {}

        ~String() { delete[] buffer ; }

        String( String&& that ) : String() { swap(that) ; } // you may want to ignore this for now

        // simple(st) assignment operator: take rhs by value and swap
        String& operator = ( String that ) { swap(that) ; return *this ; }

        std::size_t length() const { return size ; }

        char& operator[] ( std::size_t pos ) { my_assert( pos < size ) ; return buffer[pos] ; }
        const char& operator[] ( std::size_t pos ) const { my_assert( pos < size ) ; return buffer[pos] ; }

        void swap( String& that )
        {
            const auto s = size ; size = that.size ; that.size = s ;
            const auto b = buffer ; buffer = that.buffer ; that.buffer = b ;
        }

        String& operator += ( const String& that )
        {
            String temp( size + that.size ) ; // makes operator+= exception safe
            copy( buffer, buffer+size, temp.buffer ) ;
            copy( that.buffer, that.buffer+that.size, temp.buffer+size ) ;
            swap(temp) ;
            return *this ;
        }

        friend bool operator== ( const String& a, const String&b )
        { return equal( a.buffer, a.buffer+a.size, b.buffer, b.buffer+b.size ) ; }

        friend bool operator< ( const String& a, const String&b )
        { return lex_less( a.buffer, a.buffer+a.size, b.buffer, b.buffer+b.size ) ; }


        friend std::ostream& operator<< ( std::ostream& stm, const String& s ) { return stm << s.buffer ; }
};

inline String operator+ ( String a, const String& b ) { return a += b ; }
inline bool operator!= ( const String& a, const String& b ) { return !(a==b) ; }
inline bool operator> ( const String& a, const String&b ) { return b < a ; }
inline bool operator<= ( const String& a, const String&b ) { return !(a>b) ; }
inline bool operator>= ( const String& a, const String&b ) { return !(a<b) ; }

int main()
{
    String s1 = "hello" ;
    const String s2 = "world!" ;
    s1 += s2 ;
    const auto s3 = s1 + "!" ;
    my_assert( s3 > s1 ); // print message and abort if assertion fails

    // ...

    std::cout << "\n\n*** result: SUCCESS\n" ;
    
    std::cout << "\ndeliberately trigger an assertion failure: " ;
    my_assert( "this assertion must fail" == nullptr) ;
}
