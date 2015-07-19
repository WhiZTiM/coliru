#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/adapted/struct/define_struct_inline.hpp>
#include <iostream>

struct A{};
struct B{};

BOOST_FUSION_DEFINE_STRUCT_INLINE(
        Synthesized,
        (A,    a)
        (int,  i)
        (B,    b)
        )

void demonstrator()
{
    using namespace boost::spirit::qi;
    typedef const char* Iter;

    rule< Iter, A()>      ra;
    rule< Iter, B()>      rb;
    rule< Iter, int()>    rint;

//   these work:
//   rule< Iter, Synthesized()> rsynth = ra > rint > rb;
//   rule< Iter, Synthesized()> rs2 = ra >> rint >> rb;
//   rule< Iter, Synthesized()> rs3 = ra >> (rint > rb);

    // this one fails:"error: invalid static_cast from type 'const B' to type 'int'" in boost/spirit/home/qi/detail/assign_to.hpp:152:18
    rule< Iter, Synthesized()> rs4 = ra >> rint > rb;

}


int main()
{
    std::cout << "Using Boost "     
          << BOOST_VERSION / 100000     << "."  // major version
          << BOOST_VERSION / 100 % 1000 << "."  // minor version
          << BOOST_VERSION % 100                // patch level
          << std::endl;
    return 0;
    
}