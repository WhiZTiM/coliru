#define BOOST_RESULT_OF_USE_TR1
#include <iostream>
#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/qi.hpp>

struct C1 {
   std::string h;
   int i;

   friend std::ostream& operator<<(std::ostream& os, C1 const& c1) {
       return os << "C1 {h:'" << c1.h << "', i:'" << c1.i << "'}";
   }
};

struct C2 {
   std::string h;
   std::string c;

   friend std::ostream& operator<<(std::ostream& os, C2 const& c2) {
       return os << "C2 {h:'" << c2.h << "', c:'" << c2.c << "'}";
   }
};

BOOST_FUSION_ADAPT_STRUCT(C1, (std::string, h)(int, i))
BOOST_FUSION_ADAPT_STRUCT(C2, (std::string, h)(std::string, c))

typedef boost::variant<C1, C2> VariantType;
namespace qi = boost::spirit::qi;

int main() {
    VariantType value;
    char const* tests[] = { "C2:Zoo3", "C1:1234", 0 };
    for(char const** sz = tests; *sz; ++sz) {
        std::string const s1(*sz);

        if(qi::parse(s1.begin(), s1.end(), 
                    (qi::string("C1") >> ":" >> qi::int_) | 
                    (qi::string("C2") >> ":" >> *qi::char_), 
                    value)) 
            std::cout << "Parsing Succeeded: " << value << "\n";
        else             
            std::cout << "Parsing Failed" << std::endl;
    }
}
