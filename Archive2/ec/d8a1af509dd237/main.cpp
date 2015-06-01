#include <iostream>
#include <string>
#include <cstring>

template < typename T > class myclass {

    T a, b;

    static std::string bigger( const std::string& a, const std::string& b ) { // overload for strings
        return a.length() > b.length() ? a : b ; }

    static const char* bigger( const char* a, const char* b ) { // overload for const c-strings
        auto alen = a ? std::strlen(a) : 0 ;
        auto blen = b ? std::strlen(b) : 0 ;
        return alen > blen ? a : b ;
    }

    static char* bigger( char* a, char* b ) { // overload for c-strings
        auto alen = a ? std::strlen(a) : 0 ;
        auto blen = b ? std::strlen(b) : 0 ;
        return alen > blen ? a : b ;
    }

    template < typename U > static U bigger( const U& a, const U& b ) { // overload for other types
        return a > b ? a : b ; }

    public:
        myclass( const T& x, const T& y ) : a(x), b(y) {}

        void resolve() const {
            std::cout << "bigger( " << a << ", " << b << " ) is: " << bigger(a,b) << '\n' ; }
};

int main(){

	myclass<int>(30,25).resolve() ;
	myclass<float>(30.23,30.56).resolve() ;

	const char c[] = "malaga" ;
	char d[] = "jaen" ;
	myclass<std::string>(c,d).resolve() ;
	myclass<const char*>(c,d).resolve() ;

	char e[] = "jaenn" ;
    myclass<std::string>(d,e).resolve() ;
    myclass<char*>(d,e).resolve() ;
}
