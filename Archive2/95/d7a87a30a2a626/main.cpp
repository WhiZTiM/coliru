#include <iostream>
#include <memory>

template < typename T, typename ALLOCATOR = std::allocator<T> > struct colony
{
    struct group { group( int, double ) {} /* .. */ };

    explicit colony( const ALLOCATOR& a = ALLOCATOR() ) : the_allocator(a)
    {
        // type of rebound allocator
        using rebound_alloc_type = typename ALLOCATOR::template rebind<group>::other ;

        // create an object of type rebound allocator
        rebound_alloc_type rebound_allocator(the_allocator) ;

        // use the allocator object
        group* first_group = rebound_allocator.allocate(1) ;
        rebound_allocator.construct( first_group, 12, 34.56 ) ;
        std::cout << "group* first_group == " << first_group << '\n' ;
        // etc.

        // ...
    }

    // ...

    private:
        ALLOCATOR the_allocator ;
        group* ptr = nullptr ;
};

int main()
{
    colony<int> c ;
}