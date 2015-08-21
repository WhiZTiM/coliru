                                                                                                                                                                                                                                #include <type_traits>
                                                                                                                                                                                                                                #include <boost/preprocessor/cat.hpp>
                                                                                                                                                                                                                                #define PASTE2(a, b) BOOST_PP_CAT(a, b)
                                                                                                                                                                                                                                #define PASTE3(a, b, c) BOOST_PP_CAT(a, BOOST_PP_CAT(b, c))
                                                                                                                                                                                                                                #define TEST(name, t)  template<typename T, bool> int PASTE3(t, _, name)(); auto PASTE2(check_, __COUNTER__) = PASTE3(t, _, name)<t, name<t>::value>();
                                                                                                                                                                                                                                #define TEST_ALL(name) TEST(is_trivially_constructible, name) TEST(is_trivially_destructible, name) TEST(is_trivially_copyable, name)
                                                                                                                                                                                                                                using namespace std;


struct A { };
struct B { B() {} };
struct C { C(const C&) {} };
struct D { ~D() {} };


TEST_ALL(A)
TEST_ALL(B)
TEST_ALL(C)
TEST_ALL(D)
