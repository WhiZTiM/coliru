struct failed {};

template<bool C>
struct assert
{
    typedef void* type;
};
template<>
struct assert<false>
{
    typedef assert type;
};


#define STATIC_ASSERT(expr, msg) \
struct msg; \
template<bool C> \
struct msg_ { \
    static int assertion_failed(typename assert<C>::type); \
    static failed ************ (failed::************ assert_me()) (void) { return 0; } \
}; \
enum { msg##_enum = sizeof( msg_<expr>::assertion_failed( msg_<expr>::assert_me() ) ) }

template<bool B>
void test()
{
    STATIC_ASSERT(B, test_asssertion);
}

int main()
{
    test<false>();
}