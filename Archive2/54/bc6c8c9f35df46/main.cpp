#include <boost/spirit/include/karma.hpp>

namespace karma = boost::spirit::karma;

int main() {


    using namespace karma;


    for (int i = 0; i < 10; ++i)
    {
        bool b = (0 == i%3);
        std::cout << format_delimited(
                (omit[bool_(true)] << "array" | omit[bool_(false) << "vector"]),
                ';',
                b
            ) << "\n";
    }

}
