#include <iostream>
#include <memory>
#include <type_traits>

class Type
{
    public:
    template< class T >
    Type( T a )
    {
        _t = std::make_shared< T >( a );
        _info = std::addressof( typeid( T ) );
    }
    
    template< class T >
    typename std::enable_if< std::is_integral< T >::value, T >::type*
    ptr()
    {
        static_assert( not std::is_void< T >::value, "Void not allowed here" );
        if( typeid( T ) != *_info )
            throw std::logic_error("Types are differents" );
        return static_cast< T* >( _t.get() );
    }
    private:
    std::shared_ptr< void > _t = nullptr;
    const std::type_info* _info = nullptr;
};

int main()
{
    int a = 16;
    Type t( a );
    std::cout << *(t.ptr< int >()) << std::endl;
    
    try
    {
        double b = 30;
        Type t2( b );
        std::cout << *(t2.ptr< int >()) << std::endl;
    }
    catch( const std::exception & e )
    {
        std::cerr << "Error whilst returning the pointer: " << e.what() << std::endl;
    }
    
    return 0;
}
