#include <iostream>
#include <memory>

struct triangle : std::enable_shared_from_this<triangle>
{
    static std::shared_ptr<triangle> create( /* constructor_args */ )
    { return std::shared_ptr<triangle>( new triangle( /* constructor_args */ ) ) ; }

    std::shared_ptr<triangle> pointer() { return shared_from_this(); }
    std::shared_ptr< const triangle > pointer() const
    { return const_cast<triangle*>(this)->pointer(); }

    virtual ~triangle() { std::cout << "triangle " << this << " destructor\n" ; } // for tracing what is going on
    // ...

    protected: triangle( /* constructor_args */ ) /* init */
    { /* ... */ std::cout << "triangle " << this << " constructor\n" ; } // for tracing what is going on
};

int main()
{
    auto ptr1 = triangle::create( /* constructor_args */ ) ;
    std::cout << "ptr1 points to triangle at: " << ptr1.get() << '\n' ;

    if(ptr1)
    {
        triangle& t = *ptr1 ;
        auto ptr2 = t.pointer() ;
        std::cout << "ptr2 points to triangle at: " << ptr2.get() << '\n' ;

        const triangle& ct = t ;
        std::shared_ptr<const triangle > ptr3 = ct.pointer() ;
        std::cout << "ptr3 points to triangle at: " << ptr3.get() << '\n' ;
    }

    // uncomment the code below to engender undefined behaviour
    /*
    if(ptr1)
    {
        triangle& t = *ptr1 ;
        auto ptr2 = std::shared_ptr<const triangle >( std::addressof(t) ) ;
        std::cout << "ptr2 points to triangle at: " << ptr2.get() << '\n' ;
    }
    */
}
