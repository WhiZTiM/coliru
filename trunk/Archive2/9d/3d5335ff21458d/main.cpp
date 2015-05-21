#include <cerrno>
#include <cstring>
#include <iostream>

#define E_MY_USER_DEFINED_ERROR -1

struct Event
{
    int fd;
    int errnum;
};

struct Foo
{
    Foo( int sz ) : count(0), size(sz) {}

    Event open( const char name[] )
    {
        if( count >= size )
            return { -1, E_MY_USER_DEFINED_ERROR };

        int fd = std::strlen(name); // TODO: open ressource...
        if (fd < 0) return { -1, errno };
        else        return { fd, 0 };
    }

    int count, size;
};

int main()
{
    Foo bar(0);
    Event e = bar.open("my-ressource");
    
    std::cout << std::strerror( e.errnum ) << std::endl;
}