#include <type_traits>

template <typename T> class Matrix
 {
    // http://en.cppreference.com/w/cpp/types/common_type
    template< typename A, typename B >
    friend Matrix< typename std::common_type<A,B>::type > operator*( const Matrix<A>&, const Matrix<B>& );

    // .......
    private: int test = 10 ;
};

template< typename A, typename B >
Matrix< typename std::common_type<A,B>::type > operator*( const Matrix<A>& a, const Matrix<B>& b )
{
    Matrix< typename std::common_type<A,B>::type > result ;
    /*calculations happen*/
    result.test = a.test * b.test ;
    return result ;
}

int main()
{
    Matrix<short> s ;
    Matrix<int> i ;
    Matrix<double> d ;

    Matrix<int> result = s * i ;
    
    // http://en.cppreference.com/w/cpp/types/is_same
    static_assert( std::is_same< decltype( d * result ), Matrix<double> >::value,
                   "expected the common type to be double" ) ;
}
