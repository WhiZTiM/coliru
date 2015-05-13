
template<bool C> struct assert        { typedef void* type; };
template<>       struct assert<false> { typedef assert type; };


#define STATIC_ASSERT(expr, msg)                                           \
struct assertion_failed {                                                  \
    static int msg(typename assert<expr>::type);                                  \
    static void* assert_me() { return 0; }                                 \
};                                                                         \
enum { msg##_enum = sizeof( assertion_failed::msg( assertion_failed::assert_me() ) ) }

template<bool B>
void test()
{
    STATIC_ASSERT(B, B_must_not_be_false);
}

int main()
{
    test<false>();
}