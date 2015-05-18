#ifdef CRAPPYCOMPILER

struct _ {};
template<bool C> struct assert        { typedef _ type; };
template<>       struct assert<false> { typedef assert type; };

#define STATIC_ASSERT(expr, msg) (void)sizeof( msg::assertion_failed<expr>(_()) )

#define DEFINE_ASSERT_MESSAGE(msg)                                          \
struct msg {                                                                \
    template<bool C> static int assertion_failed(typename assert<C>::type); \
}

#else

#define DEFINE_ASSERT_MESSAGE(msg)
#define STATIC_ASSERT(expr, msg) static_assert((expr), #msg)

#endif

// -----------------------------------------------------------------
template<typename A, typename B>
struct is_same { static const bool value = false; };

template<typename T>
struct is_same<T,T> { static const bool value = true; };

// -----------------------------------------------------------------

// user code defines "compile-time exceptions" before use
DEFINE_ASSERT_MESSAGE(expected_int_type);

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
