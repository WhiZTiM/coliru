template<bool C> struct assert        { typedef void* type; };
template<>       struct assert<false> { typedef assert type; };

/* define all assert "messages" here */
struct expected_int_type { 
    template<bool C> 
    static int assertion_failed(typename assert<C>::type);
};

/* end assert messages */

#define STATIC_ASSERT(expr, msg) (void)sizeof( msg::assertion_failed<expr>(0) )

template<typename A, typename B>
struct is_same { static const bool value = false; };

template<typename T>
struct is_same<T,T> { static const bool value = true; };

template<typename T>
void test(T)
{
    STATIC_ASSERT( (is_same<T,int>::value), expected_int_type);
}

int main()
{
	test(1);
	test(1.5);
}
