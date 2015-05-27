#include <boost/spirit/include/qi.hpp>

int main() {
    static_assert(boost::spirit::traits::is_container<std::string>::value, "is a container");
    static_assert(boost::spirit::traits::is_string<std::string>::value, "is a container");
}
