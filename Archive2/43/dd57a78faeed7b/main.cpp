#include <iostream>
#include <string>
#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;
namespace ascii= boost::spirit::ascii;

void print_language(const std::string& v)
{
    std::cout << "language: " << v << '\n';
}

void print_script(const std::string& v)
{
    std::cout << "script: " << v << '\n';
}

void print_variant(const std::string& v)
{
    std::cout << "variant: " << v << '\n';
}

void print_extension(const std::string& v)
{
    std::cout << "extension: " << v << '\n';
}

void print_private(const std::string& v)
{
    std::cout << "private: " << v << '\n';
}

void print_region(const std::string& v)
{
    std::cout << "region: " << v << '\n';
}

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
struct ietf_language_tag_grammar : qi::grammar<Iterator, std::vector<std::string>()>
{
    ietf_language_tag_grammar() : ietf_language_tag_grammar::base_type(tag)
    {
        using qi::no_case;
        using qi::char_;
        using qi::repeat;
        using qi::inf;
        using qi::hold;

        using ascii::alpha;
        using ascii::digit;
        using ascii::alnum;

        tag %= no_case[langtag];

        langtag %= language[print_language]
                >> -('-' >> script[print_script])
                >> -('-' >> region[print_region])
                >> *('-' >> variant[print_variant])
                >> *('-' >> extension[print_extension])
                >> -('-' >> privateuse[print_private]);

        language %= hold[((repeat(2, 3)[alpha] >> -('-' >> hold[extlang])) >> !alnum)]
                  | hold[(repeat(5, 8)[alpha] >> !alnum)]
                  | (repeat(4)[alpha] >> !alnum);


        extlang %= repeat(3)[alpha] >> repeat(0,2)['-' >> repeat(3)[alpha]] >> !alnum;

        script %= repeat(4)[alpha] >> !alnum;

        region %= hold[(repeat(2)[alpha] >> !alnum)]   // ISO-3166-1 code
                | (repeat(3)[digit] >> !alnum);  // UN M.49 code

        variant %= hold[(repeat(5, 8)[alnum] >> !alnum)]
                 | ((digit >> repeat(3)[alnum]) >> !alnum);

        extension %= singleton >> repeat(1, inf)['-' >> repeat(2, 8)[alnum]];

        singleton %= (alnum - 'x');

        privateuse %= 'x' >> repeat(1, inf)['-' >> repeat(1, 8)[alnum]];
    }

    qi::rule<Iterator, std::vector<std::string>()> tag;
    qi::rule<Iterator, std::vector<std::string>()> langtag;

    qi::rule<Iterator, std::string()> language;
    qi::rule<Iterator, std::string()> extlang;
    qi::rule<Iterator, std::string()> script;
    qi::rule<Iterator, std::string()> region;
    qi::rule<Iterator, std::string()> variant;
    qi::rule<Iterator, std::string()> extension;
    qi::rule<Iterator, char()> singleton;
    qi::rule<Iterator, std::string()> privateuse;
};

template<typename ConstIter>
bool parse_ietf_tag(ConstIter begin, ConstIter end)
{
    using qi::parse;

    static const ietf_language_tag_grammar<ConstIter> grammar;

    std::vector<std::string> result;
    bool r = parse(begin, end, grammar, result);

    if (begin != end)
    {
        std::cout << "did not hit end|";
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
        "zh-CN-a-myext-x-private",
        "abcdefgh"
    };


    for (const std::string& input : inputs)
    {
        std::cout << "is '" <<  input << "' a valid language tag?\n";
        bool valid_tag = parse_ietf_tag(input.begin(), input.end());
        std::cout << std::boolalpha << valid_tag << "\n\n";
    }

    return EXIT_SUCCESS;
}
