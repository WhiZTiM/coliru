#include <iostream>
#include <string>
#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;
namespace ascii= boost::spirit::ascii;

struct ietf_tag
{
    std::string val;
    ietf_tag()
    {
    }

    ietf_tag (const std::string& v)
        : val(v)
    {
    }
};

template <typename Iterator>
struct ietf_language_tag_grammar : qi::grammar<Iterator, ietf_tag(), ascii::space_type>
{
    ietf_language_tag_grammar() : ietf_language_tag_grammar::base_type(tag)
    {
        using qi::no_case;
        using qi::char_;
        using qi::repeat;
        using qi::alpha;
        using qi::digit;
        using qi::alnum;
        using boost::spirit::inf;

        tag = no_case[langtag];

        langtag = language
                >> -('-' >> script)
                >> -('-' >> region)
                >> *('-' >> variant)
                >> *('-' >> extension)
                >> -('-' >> privateuse);

        language = (repeat(2, 3)[alpha] >> -extlang)
                 | repeat(4)[alpha]
                 | repeat(5, 8)[alpha];

        extlang = repeat(3)[alpha] >> repeat(0,2)['-' >> repeat(3)[alpha]];

        script = repeat(4)[alpha];

        region = repeat(2)[alpha]   // ISO-3166-1 code
               | repeat(3)[digit];  // UN M.49 code

        variant = repeat(5, 8)[alnum]
                | (digit >> repeat(3)[alnum]);

        extension = singleton >> repeat(1, inf)['-' >> repeat(2, 8)[alnum]];

        singleton = digit
                  | char_('a', 'w')
                  | char_('y', 'z');

        privateuse = 'x' >> repeat(1, inf)['-' >> repeat(1, 8)[alnum]];
    }

    qi::rule<Iterator, ietf_tag(), ascii::space_type> tag;
    qi::rule<Iterator, ietf_tag(), ascii::space_type> langtag;

    qi::rule<Iterator, std::string(), ascii::space_type> language;
    qi::rule<Iterator, std::string(), ascii::space_type> extlang;
    qi::rule<Iterator, std::string(), ascii::space_type> script;
    qi::rule<Iterator, std::string(), ascii::space_type> region;
    qi::rule<Iterator, std::string(), ascii::space_type> variant;
    qi::rule<Iterator, std::string(), ascii::space_type> extension;
    qi::rule<Iterator, char(), ascii::space_type> singleton;
    qi::rule<Iterator, std::string(), ascii::space_type> privateuse;
};

template<typename ConstIter>
bool parse_ietf_tag(ConstIter begin, ConstIter end)
{
    using qi::double_;
    using qi::phrase_parse;
    using ascii::space;

    static const ietf_language_tag_grammar<ConstIter> grammar;

    bool r = phrase_parse(begin,
                          end,
                          grammar,
                          space);

    if (begin != end)
    {
        return false;
    }
    return r;

}

int main()
{
    std::string inputs[] =
    {
        "en-gb",
        "en-AU",
        "en-US",
        "en_AU", // only FALSE test case, everything eles should pass
        "zh-Hant",
        "zh-Hans",
        "sr-Cyrl",
        "sr-Latn",
        "zh-cmn-Hans-CN",
        "cmn-Hans-CN",
        "zh-yue-HK",
        "yue-HK",
        "zh-Hans-CN",
        "sr-Latn-RS",
        "sl-rozaj",
        "sl-rozaj-biske",
        "sl-nedis",
        "de-CH-1901",
        "sl-IT-nedis",
        "hy-Latn-IT-arevela",
        "es-419",
        "x-whatever"
    };

    for (const std::string& input : inputs)
    {
        bool valid_tag = parse_ietf_tag(input.begin(), input.end());
        std::cout << "is '" <<  input << "' a valid language tag? " << std::boolalpha << valid_tag << '\n';
    }
    
    return EXIT_SUCCESS;
}
