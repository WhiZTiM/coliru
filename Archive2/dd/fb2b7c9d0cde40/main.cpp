#include <iostream>
#include <fstream>

template < typename C, typename T = std::char_traits<C> >

struct basic_teebuf : public std::basic_streambuf<C,T>
{
    typedef std::basic_streambuf<C,T> streambuf_type ;
    typedef typename T::int_type int_type ;

    basic_teebuf( streambuf_type* buff_a, streambuf_type* buff_b )
            : first(buff_a), second(buff_b) {}

    std::pair<streambuf_type*, streambuf_type*> buffers()
    {
        return {first, second};
    }

    protected:
        virtual int_type overflow( int_type c )
        {
            const int_type eof = T::eof() ;
            if( T::eq_int_type( c, eof ) ) return T::not_eof(c) ;
            else
            {
                const C ch = T::to_char_type(c) ;
                if( T::eq_int_type( first->sputc(ch), eof ) ||
                    T::eq_int_type( second->sputc(ch), eof ) )
                        return eof ;
                else return c ;
            }
        }

        virtual int sync()
        { return !first->pubsync() && !second->pubsync() ? 0 : -1 ; }

    private:
        streambuf_type* first ;
        streambuf_type* second ;
};

typedef basic_teebuf<char> teebuf ;

int main()
{

    std::ofstream file( "out.txt" ) ;
    //Constructing our tee buffer
    teebuf foo(std::cout.rdbuf(), file.rdbuf());
    //replacing default cout buffer with ours
    std::cout.rdbuf(&foo);
    try {
        //Do our stuff here        
        std::cout << "Test\n";
        std::cout << 123 << '\n';

        //restore cout buffer
        std::cout.rdbuf(foo.buffers().first);
    } catch(...) {
        std::cout.rdbuf(foo.buffers().first);
        throw;
    }
}
