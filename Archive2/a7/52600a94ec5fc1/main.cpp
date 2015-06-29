#include <iostream>
#include <cassert>
#include <algorithm>
#include <cstring>

class String {

    std::size_t size = 0 ;
    char * buffer = new char[0]{};

    public:
        String() = default ;

        String( const String& that ) : size(that.size), buffer( new char[size]{} )
        { std::copy( that.buffer, that.buffer+size, buffer ) ; }

        String( const char* cstr ) : size( cstr ? std::strlen(cstr) : 0 ), buffer( new char[size]{} )
        { std::copy( cstr, cstr+size, buffer ) ; }

        String( std::size_t len ) : size(len), buffer( new char[size]{} ) {}

        ~String() { delete[] buffer ; }

        String( String&& that ) : String() { swap(that) ; }

        // simple(st) assignment operator: take rhs by value and swap
        String& operator = ( String that ) { swap(that) ; return *this ; }

        std::size_t length() const { return size ; }

        char& operator[] ( std::size_t pos ) { assert( pos < size ) ; return buffer[pos] ; }
        const char& operator[] ( std::size_t pos ) const { assert( pos < size ) ; return buffer[pos] ; }

        void swap( String& that ) { std::swap(size,that.size) ; std::swap(buffer,that.buffer) ; }

        String& operator += ( const String& that )
        {
            String temp( size + that.size ) ;
            std::copy( buffer, buffer+size, temp.buffer ) ;
            std::copy( that.buffer, that.buffer+that.size, temp.buffer+size ) ;
            swap(temp) ;
            return *this ;
        }

        friend String operator+ ( String a, const String& b ) { return a += b ; }

        friend bool operator== ( const String& a, const String&b )
        { return std::equal( a.buffer, a.buffer+a.size, b.buffer, b.buffer+b.size ) ; }

        friend bool operator< ( const String& a, const String&b )
        { return std::lexicographical_compare( a.buffer, a.buffer+a.size, b.buffer, b.buffer+b.size ) ; }

        friend bool operator!= ( const String& a, const String& b ) { return !(a==b) ; }
        friend bool operator> ( const String& a, const String&b ) { return b < a ; }
        friend bool operator<= ( const String& a, const String&b ) { return !(a>b) ; }
        friend bool operator>= ( const String& a, const String&b ) { return !(a<b) ; }

        friend std::ostream& operator<< ( std::ostream& stm, const String& s ) { return stm << s.buffer ; }
};

int main()
{
    String s1; // s1 == ""
    assert(s1.length() == 0);

    String s2("hi");  // s2 == "hi"
    assert(s2.length() == 2);

    String s3(s2);  // s3 == "hi"
    assert(s3.length() == 2);

    assert(s3[0] == 'h');
    assert(s3[1] == 'i');

    s1 = s2;  // s1 == "hi"
    assert(s1 == s2);

    s3 = "bye";  // s3 == "bye"
    assert(s3.length() == 3);
    assert(s3[0] == 'b');
    assert(s3[1] == 'y');
    assert(s3[2] == 'e');

    s1 += "re";  // s1 == "hire"
    assert(s1 == "hire");

    s1 += "d"; // s1 == "hired"
    assert(not (s1 == "hire"));

    s1 = std::move(s2) ;
    assert( s1 == "hi" ) ;

    std::cout << "SUCCESS" << '\n' ;
}
