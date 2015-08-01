    #include <type_traits>
    #include <utility>
    #include <iostream>
    
    #include <boost/variant.hpp>
    
    #include <cstdlib>
    
    namespace
    {
        
    struct A {};
    struct B {};
    struct C {};
    
    using V = boost::variant< A, B, C >;
    
    struct visitor
    {
        
        using result_type = void;
    
        result_type
        operator () (V v) const
        {
    #if 1
            return boost::apply_visitor([this] (auto && x) -> result_type { return apply(std::forward< decltype(x) >(x)); }, v);
        }
    #else
            return boost::apply_visitor(*this, v);
        }
        
        template< typename T >
        result_type
        operator () (T && x) const
        {
            return apply(std::forward< T >(x));
        }
    #endif
        
    private :
        
        result_type
        apply(A) const
        {
            std::cout << __PRETTY_FUNCTION__ << std::endl;
        }
        
        template< typename T >
        result_type
        apply(T &&) const
        {
            std::cout << __PRETTY_FUNCTION__ << std::endl;
        }
        
    public : // !
        
    };
    
    }
    
    int
    main()
    {
        visitor{}(V{B{}});
        return EXIT_SUCCESS;
    }
