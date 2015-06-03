#include <iostream>
#include <string>
#include <algorithm>

namespace detail
{
    struct bigger_value
    {
        template < typename T >
        T operator() ( const T& a, const T& b ) const { return a > b ? a : b ; }

    };

    struct bigger_size
    {
        template < typename T >
        T operator() ( const T& a, const T& b ) const { return a.size() > b.size() ? a : b ; }
    };
}

namespace A // implementor (and not the user) specifies the resolve policy
            // resolve policy is an encapsulated implementation detail
{
    template < typename T > class myclass {

        T a, b;

        static std::string bigger( const std::string& a, const std::string& b ) { // overload for strings
            return detail::bigger_size()(a,b) ; }

        template < typename U > static U bigger( const U& a, const U& b ) { // overload for other types
            return detail::bigger_value()(a,b) ; ; }

        public:
            myclass( const T& x, const T& y ) : a(x), b(y) {}

            T resolve() const { return bigger(a,b) ; }
    };
}

namespace B // policy parameterisation: the user can specify the resolve policy,
            // once, right at the beginning, when the type is specified
{
    template < typename T, typename BIGGER = detail::bigger_value > class myclass {

        T a, b;
        BIGGER bigger ; // make a copy; the policy object can have state

        public:
            // accept a policy object; it need not be default-constructible
            myclass( const T& x, const T& y, const BIGGER& cmp = BIGGER() ) : a(x), b(y), bigger(cmp) {}

            T resolve() const { return bigger(a,b) ; }
    };
}

namespace C // the user can specify the resolve policy, each time resolve is to be called
{
    template < typename T > class myclass {

        T a, b;

        public:
            myclass( const T& x, const T& y ) : a(x), b(y) {}

            T resolve() const { return std::max(a,b) ; }

            template < typename BIGGER > T resolve( const BIGGER& bigger = BIGGER() ) const {
                return bigger(a,b) ; }
    };
}

#define RESOLVE(a) ( std::cout << #a << ".resolve(): " << (a).resolve() << "\n\n" )

int main(){

    RESOLVE( A::myclass<int>(30,25) ) ;
    RESOLVE( A::myclass<std::string>( "malaga", "jaennnn" ) ) ;
    std::cout << "-------------------------\n\n" ;

    RESOLVE( B::myclass<int>(30,25) ) ;
    RESOLVE( B::myclass<std::string>( "malaga", "jaennnn" ) ) ;
    RESOLVE( ( B::myclass< std::string, detail::bigger_size >( "malaga", "jaennnn" ) ) ) ;
    std::cout << "-------------------------\n\n" ;

    RESOLVE( C::myclass<int>(30,25) ) ;
    std::cout << "C::myclass<int>(30,25).resolve( [] ( int a, int b ) { return a%10 > b%10 ? a : b ; } ): "
              << C::myclass<int>(30,25).resolve( [] ( int a, int b ) { return a%10 > b%10 ? a : b ; } ) << "\n\n" ;

    C::myclass<std::string> mc( "malaga", "jaennnn" );
    RESOLVE(mc) ;
    std::cout << "mc.resolve<detail::bigger_size>(): " << mc.resolve<detail::bigger_size>() << "\n\n" ;
    std::cout << "mc.resolve( detail::bigger_size() ): " << mc.resolve( detail::bigger_size() ) << "\n\n" ;
}
