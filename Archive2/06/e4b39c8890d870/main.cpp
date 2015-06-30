#include <iostream>

[[ noreturn ]] [[ deprecated( "instead, use the assert in <cassert>" ) ]]
static bool my_assert_( const char* text, const char* source_file, unsigned int line )
{
   std::cerr <<  "\n\nassertion '" << text << "' failed: file: "
             << source_file << " line: " << line << '\n' ;
             
   struct assertion_failure {}; throw assertion_failure {} ;
   // note: without a handler, default behaviour is: 
   // std::terminate() => std::terminate_handler => std::abort()
}

#ifdef NDEBUG
    #define my_assert(e) static_cast<void>(0)
#else
    #define my_assert(e) static_cast<void>( ( (!!(e)) || my_assert_( #e, __FILE__, __LINE__ ) ), 0 )
#endif // NDEBUG

class String {

    std::size_t size ;
    char * buffer ;

    static std::size_t strlen( const char* p )
    {
        std::size_t n = 0 ;
        if( p != nullptr ) while( *p++ != 0 ) ++n ;
        return n ;
    }

    static void copy( const char* begin, const char* end, char* dest )
    { if( begin && end && dest ) while( begin != end ) *dest++ = *begin++ ; }

    static bool equal( const char* beg_a, const char* end_a, const char* beg_b, const char* end_b )
    {
        for( ; beg_a != end_a && beg_b != end_b ; ++beg_a, ++beg_b )
            if( *beg_a != *beg_b ) return false ;
        return beg_a == end_a && beg_b == end_b ; // reached end of both sequences
    }

    static bool lex_less( const char* beg_a, const char* end_a, const char* beg_b, const char* end_b )
    {
        for( ; beg_a != end_a && beg_b != end_b ; ++beg_a, ++beg_b )
            if( *beg_a < *beg_b ) return true ;
            else if ( *beg_b < *beg_a ) return false ;
        return beg_a == end_a && beg_b != end_b ; // reached end of both sequences
    }

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

        friend String operator+ ( String a, const String& b ) { return a += b ; }

        friend bool operator== ( const String& a, const String&b )
        { return equal( a.buffer, a.buffer+a.size, b.buffer, b.buffer+b.size ) ; }

        friend bool operator< ( const String& a, const String&b )
        { return lex_less( a.buffer, a.buffer+a.size, b.buffer, b.buffer+b.size ) ; }

        friend bool operator!= ( const String& a, const String& b ) { return !(a==b) ; }
        friend bool operator> ( const String& a, const String&b ) { return b < a ; }
        friend bool operator<= ( const String& a, const String&b ) { return !(a>b) ; }
        friend bool operator>= ( const String& a, const String&b ) { return !(a<b) ; }

        friend std::ostream& operator<< ( std::ostream& stm, const String& s ) { return stm << s.buffer ; }
};

int main()
{
    try { my_assert( "this assertion should fail" == nullptr ) ; }
    catch( ... ) { std::clog << "this is an expected assertion failure\n" ; /* return 1 ; */ }
        
    String s1; // s1 == ""
    my_assert(s1.length() == 0);

    String s2("hi");  // s2 == "hi"
    my_assert(s2.length() == 2);

    String s3(s2);  // s3 == "hi"
    my_assert(s3.length() == 2);

    my_assert(s3[0] == 'h');
    my_assert(s3[1] == 'i');

    s1 = s2;  // s1 == "hi"
    my_assert(s1 == s2);

    s3 = "bye";  // s3 == "bye"
    my_assert(s3.length() == 3);
    my_assert(s3[0] == 'b');
    my_assert(s3[1] == 'y');
    my_assert(s3[2] == 'e');

    s1 += "re";  // s1 == "hire"
    my_assert(s1 == "hire");

    s1 += "d"; // s1 == "hired"
    my_assert( not ( s1 == "hire" ) );

    s1 = std::move(s2) ;
    my_assert( s1 == "hi" ) ;

    std::cout << "\n\nresult: SUCCESS\n" ;
}
