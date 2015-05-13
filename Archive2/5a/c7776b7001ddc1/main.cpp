#ifdef CRAPPY_COMPILER

template<bool C> struct assert        { typedef void* type; };
template<>       struct assert<false> { typedef assert type; };

/* define all assert "messages" here */
struct types_must_match { 
    template<bool C> 
    static int assertion_failed(typename assert<C>::type);
};

struct precision_loss_in_conversion {
    template<bool C>
    static int assertion_failed(typename assert<C>::type);
};
/* end assert messages */

#define STATIC_ASSERT(expr, msg) (void)sizeof( msg::assertion_failed<expr>(0) )

#else

#define STATIC_ASSERT(expr, msg) static_assert(expr, #msg)

#endif


template<bool B>
void test()
{
    STATIC_ASSERT(B, types_must_match);
}

int main()
{
    test<true>();
    
    test<false>();
}