#include <type_traits>

// CRTP template, derived class must pass itself to base.
    template< class derived >
    struct base_interface {
        base_interface() {
            static_assert ( std::is_same< decltype( derived::calculate_something() ),
                                          typename derived::value_type >::value,
                "derived class is missing calculate_something" );
        }
        
        static struct invalid calculate_something();
        typedef void value_type;
    };

struct good_derived : base_interface< good_derived > {
    typedef int value_type;
    
    static value_type calculate_something() { return 42; }
};

struct bad_derived : base_interface< bad_derived > {
};

good_derived g;
bad_derived b;
