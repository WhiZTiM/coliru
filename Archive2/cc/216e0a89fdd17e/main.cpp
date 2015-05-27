#include <iostream>
#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/qi.hpp>

struct C1 {
   std::string h{""};
   int i{0};

   friend std::ostream& operator<<(std::ostream& os, C1 const& c1) {
       return os << "C1 {h:'" << c1.h << "', i:'" << c1.i << "'}";
   }
};

struct C2 {
   std::string h{""};
   std::string c{};

   friend std::ostream& operator<<(std::ostream& os, C2 const& c2) {
       return os << "C2 {h:'" << c2.h << "', c:'" << c2.c << "'}";
   }
};

BOOST_FUSION_ADAPT_STRUCT(C1, (std::string, h)(int, i))
BOOST_FUSION_ADAPT_STRUCT(C2, (std::string, h)(std::string, c))

using VariantType = boost::variant<C1, C2>;
namespace qi = boost::spirit::qi;

int main() {
    VariantType value;
    for(std::string s1 : {
            "C2:Zoo3",
            "C1:1234"
            })
    {
        if(qi::parse(s1.begin(), s1.end(), 
                    (qi::string("C1") >> ":" >> qi::int_) | 
                    (qi::string("C2") >> ":" >> *qi::char_), 
                    value)) 
            std::cout << "Parsing Succeeded: " << value << "\n";
        else             
            std::cout << "Parsing Failed" << std::endl;
    }
}
