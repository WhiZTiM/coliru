#include <iostream>

class base_class
{
    public:
        virtual ~base_class() {}
        void non_virtual_function() const  { std::cout << "base_class::non_virtual_function\n" ; }
        virtual void virtual_function() const  { std::cout << "base_class::virtual_function\n" ; }
};

struct derived_class : base_class
{
    public:
        // derived_class::non_virtual_function hides base_class::non_virtual_function
        void non_virtual_function() const
        { std::cout << "derived_class::non_virtual_function hides base_class::non_virtual_function\n" ; }

        // derived_class::non_virtual_function overrides base_class::non_virtual_function
        virtual void virtual_function() const override
        { std::cout << "derived_class::virtual_function overrides base_class::virtual_function\n\n" ; }
};

void foo( const base_class& x )
{
    // the static type (type known at compile-time) of the object referred to by 'x' is base_class
    // the dynamic type (type known only at run-time, which may be different each time
    // foo is called) of the object referred to by 'x' could be a class derived from base_class

    x.non_virtual_function() ; // not virtual; bind to the function of the static type
                               // call 'base_class::non_virtual_function
                               // the same function is called every time

    x.virtual_function() ; // virtual; bind to the function of the dynamic type
                           // call ????::virtual_function where ???? is the dynamic type of he object
                           // each time foo is called, this may be a different function
}

int main()
{
    derived_class derived ;
    foo(derived) ;

    struct another : base_class
    {
        void non_virtual_function() const
        { std::cout << "*** main::another::non_virtual_function ***\n" ; }

        virtual void virtual_function() const override
        { std::cout << "*** main::another::virtual_function ***\n\n" ; }
    };

    another a ;
    foo(a) ;
}
