#include <boost/spirit/include/qi.hpp>
namespace qi = boost::spirit::qi;

enum TagTypes { NUMBER, TEXT, };

struct CMyTag {
    TagTypes tagName;
    std::string tagData;
};
BOOST_FUSION_ADAPT_STRUCT(::CMyTag, (TagTypes, tagName) (std::string, tagData))

template <typename Iterator>
struct TextWithNumbers_grammar : qi::grammar<Iterator, std::vector<CMyTag>()>
{
    TextWithNumbers_grammar() : TextWithNumbers_grammar::base_type(line)
    {
        using namespace qi;
        line      = +(numbertag | texttag);

        numbertag = attr(NUMBER) >> raw[number];
        texttag   = attr(TEXT)   >> raw[+(char_ - number)];
    }

  private:
    template <typename T>
        struct simple_real_policies : boost::spirit::qi::real_policies<T>
    {
        template <typename It> //  No exponent
            static bool parse_exp(It&, It const&) { return false; }

        template <typename It, typename Attribute> //  No exponent
            static bool parse_exp_n(It&, It const&, Attribute&) { return false; }
    };

    qi::real_parser<double, simple_real_policies<double> > number;
    qi::rule<Iterator, CMyTag()> numbertag, texttag;
    qi::rule<Iterator, std::vector<CMyTag>()> line;
};

int main() {

    std::string const input = "wernwl kjwnwenrlwe +10.90e3++ klwnfkwenwf";
    using It = std::string::const_iterator;

    It f = input.begin(), l = input.end();

    std::vector<CMyTag> data;
    TextWithNumbers_grammar<It> g;

    if (qi::parse(f, l, g, data)) {
        std::cout << "Parse success: " << data.size() << " elements\n";
        for (auto& s : data) {
            std::cout << (s.tagName == NUMBER?"NUMBER":"TEXT")
                      << "\t'" << s.tagData << "'\n";
        }
    } else {
        std::cout << "Parse failed\n";
    }

    if (f!=l)
        std::cout << "Remaining unparsed: '" << std::string(f,l) << "'\n";
}
