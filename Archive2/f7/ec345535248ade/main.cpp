#ifdef CRAPPY_COMPILER

#define STATIC_ASSERT(expr, msg) typedef int assert msg[(expr) ? 1 : -1]

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