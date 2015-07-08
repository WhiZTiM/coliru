//#pragma GCC diagnostic push
//#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
//#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
//#pragma GCC diagnostic ignored "-Wunused-variable"
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/qi.hpp>
//#pragma GCC diagnostic pop // pops

#include <iostream>

int main() {
    typedef  unsigned long long ull;

    std::string const curline = "1;2;;3,4;5";
    std::cout << "parsing: '" << curline << "'\n";

    namespace qi = boost::spirit::qi;

#if 1 // THIS IS UNDEFINED BEHAVIOUR:
    auto ids     = -qi::ulong_long % ','; // '-' allows for empty vecs.
    auto grammar = ids % ';';
#else // THIS IS CORRECT:
    auto ids     = qi::copy(-qi::ulong_long % ','); // '-' allows for empty vecs.
    auto grammar = qi::copy(ids % ';');
#endif

    std::vector<std::vector<ull> > r;
    qi::parse(curline.begin(), curline.end(), grammar, r);

    std::cout << "got:      ";
    for (auto v: r){
        for (auto i : v)
            std::cout << i << ",";
        std::cout << ";";
    }
    std::cout <<"\n";
}
