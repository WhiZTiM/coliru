#include <boost/spirit/include/qi.hpp>
#include <boost/algorithm/string/join.hpp>
#include <iostream>
#include <string>
#include <vector>
namespace client {
    namespace qi = boost::spirit::qi;

    template <typename Iterator>
        bool parseName(Iterator first, Iterator last, std::string& name) {
            static const qi::rule<Iterator, std::string()> segment = qi::alnum >> *(qi::alnum|qi::char_('_'));

            std::vector<std::string> segments;
            bool have_wildcard;

            bool r = qi::parse(
                    first, last, 
                    segment % '/' >> -qi::matches [ "/*" ],
                    segments, 
                    have_wildcard);

            r &= (first == last); // fail if we did not get a full match

            if (r) {
                if (have_wildcard)
                    segments.emplace_back("*");
                name = boost::algorithm::join(segments, "::");
            }

            return r;
        }
}

int main()
{
    //std::string str = "";
    //std::getline(std::cin, str);
    for (std::string const str : {
            "str1", 
            "str1_str", 
            "str1_str/str", 
            "str1_str/str/*", 
        })
    {
        std::string name;
        std::cout << "\n-------------------\ninput: '" << str << "'\n";
        if (client::parseName(str.begin(), str.end(), name)) {
            std::cout << "name: " << name << std::endl;
        } else {
            std::cout << "not oook\n";
        }
    }
}
