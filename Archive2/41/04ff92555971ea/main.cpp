#include <iostream>
#include <stdexcept>
#include <iterator>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <type_traits>

// this class contains pointer members, but it does not own any resources
// rule of zero may be applied
template< typename T > struct array_slice
{
    template < std::size_t N >
        array_slice( T(&a)[N], std::size_t from, std::size_t sz ) : begin_(a+from), end_(a+from+sz)
        { if( (from+sz) > N ) throw std::out_of_range("out of range slice") ; }

    using value_type = T ;
    using iterator = T* ;
    iterator begin() { return begin_ ; }
    iterator end() { return end_ ; }

    using reverse_iterator = std::reverse_iterator<iterator> ;
    reverse_iterator rbegin() { return reverse_iterator( end() ) ; }
    reverse_iterator rend() { return reverse_iterator( begin() ) ; }

    // etc.

    private:
        T* begin_ ;
        T* end_ ;
};

// this class contains no pointer/reference members, but only an int member
// but it owns a resource, and encapsulates the management and ownership of that resource
// ergo, rule of five
struct file_descriptor
{
    static constexpr int NOT_AN_FD = -1 ;

    file_descriptor() = default ;

    template< typename FN, typename... ARGS > file_descriptor( FN fn, ARGS... args ) : fd( fn(args...) ) {}

    file_descriptor( const file_descriptor& that ) noexcept : fd( that.do_dup() ) {}

    file_descriptor( file_descriptor&& that ) noexcept : file_descriptor() { std::swap( fd, that.fd ) ; }

    file_descriptor& operator= ( const file_descriptor& that ) noexcept
    {
        if( fd != that.fd )
        {
            do_close() ;
            fd = that.do_dup() ;
        }
        return *this ;
    }

    file_descriptor& operator= ( file_descriptor&& that ) noexcept
    { std::swap( fd, that.fd ) ; return *this ; }

    ~file_descriptor() noexcept { do_close() ; }

    operator int () const noexcept { return fd ; }

    private:
        int fd = NOT_AN_FD ;

        void do_close() noexcept { if( fd != NOT_AN_FD ) ::close(fd) ; }
        int do_dup() const noexcept { return fd != NOT_AN_FD ? ::dup(fd) : NOT_AN_FD ; }
};

// this class does not directly manage any owned resources
// resource management is encapsulated in the member 'fd'
// rule of zero
struct input_file
{
    input_file( const char* path ) : fd( ::open, path, O_RDONLY ) {}

    void dump_head() const
    {
        char buffer[256] {} ;
        ::write( STDOUT_FILENO, buffer, ::read( fd, buffer, sizeof(buffer) ) ) ;
        std::cout << '\n' << std::flush ;
    }

    // ...

    private: file_descriptor fd ;
};

#define show_moveable( T ) \
( \
     std::cout << std::boolalpha \
               << #T " is move constructible? " << std::is_move_constructible<T>::value << '\n' \
               << #T " is move assignable? " << std::is_move_assignable<T>::value << '\n' << std::flush \
)

int main()
{
    show_moveable( array_slice<int> ) ;
    show_moveable( file_descriptor ) ;
    show_moveable( input_file ) ;
    std::cout << "\n----------------\n\n" << std::flush ;

    int a[] { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 } ;
    array_slice<int> slice( a, 3, 5 ) ;
    for( int v : slice ) std::cout << v << ' ' ;
    std::cout << "\n----------------\n\n" << std::flush ;

    input_file file( __FILE__ ) ;
    file.dump_head() ;
}
