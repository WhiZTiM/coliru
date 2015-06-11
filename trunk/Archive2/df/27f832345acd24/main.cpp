#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/adapted/std_pair.hpp>
#include <map>

using Entity    = std::map<std::string, std::string>;
using ValveData = std::vector<Entity>;

namespace qi = boost::spirit::qi;

template <typename It, typename Skipper = qi::space_type>
struct Grammar : qi::grammar<It, ValveData(), Skipper>
{
    Grammar() : Grammar::base_type(start) {
        using namespace qi;

        start  = *entity;
        entity = '{' >> *entry >> '}';
        entry  = text >> text;
        text   = '"' >> *~char_('"') >> '"';

        BOOST_SPIRIT_DEBUG_NODES((start)(entity)(entry)(text))
    }
  private:
    qi::rule<It, ValveData(),                           Skipper> start;
    qi::rule<It, Entity(),                              Skipper> entity;
    qi::rule<It, std::pair<std::string, std::string>(), Skipper> entry;
    qi::rule<It, std::string()>                                  text;
};

int main()
{
    using It = boost::spirit::istream_iterator;
    Grammar<It> parser;
    It f(std::cin >> std::noskipws), l;

    ValveData data;
    bool ok = qi::phrase_parse(f, l, parser, qi::space, data);

    if (ok) {
        std::cout << "Parsing success:\n";

        int count = 0;
        for(auto& entity : data)
        {
            ++count;
            for (auto& entry : entity)
                std::cout << "Entity " << count << ": [" << entry.first << "] -> [" << entry.second << "]\n";
        }
    } else {
        std::cout << "Parsing failed\n";
    }

    if (f!=l)
        std::cout << "Remaining unparsed input: '" << std::string(f,l) << "'\n";
}
