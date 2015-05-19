
#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <vector>

#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

namespace qi = boost::spirit::qi;
namespace ascii= boost::spirit::ascii;

struct ietf_extension_entry
{
    char extension_name;
    std::vector<std::string> extension_values;
};

BOOST_FUSION_ADAPT_STRUCT(
    ietf_extension_entry,
    (char,                      extension_name)
    (std::vector<std::string>,  extension_values)
);

struct ietf_tag
{
    std::string language;
    std::string script;
    std::string region;
    std::vector<std::string> variants;
    std::vector<ietf_extension_entry> extensions;
    std::vector<std::string> private_use;
};

BOOST_FUSION_ADAPT_STRUCT(
    ietf_tag,
    (std::string,                               language)
    (std::string,                               script)
    (std::string,                               region)
    (std::vector<std::string>,                  variants)
    (std::vector<ietf_extension_entry>,         extensions)
    (std::vector<std::string>,                  private_use)
);


template <typename Iterator>
struct ietf_language_tag_grammar : qi::grammar<Iterator, ietf_tag()>
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

        langtag %= language
                >> -('-' >> script)
                >> -('-' >> region)
                >> *('-' >> variant)
                >> *('-' >> extension)
                >> -('-' >> privateuse);

        language %= hold[((repeat(2, 3)[alpha] >> -('-' >> hold[extlang])) >> !alnum)]
                  | hold[(repeat(5, 8)[alpha] >> !alnum)]
                  | hold[(repeat(4)[alpha] >> !alnum)];


        extlang %= hold[repeat(3)[alpha] >> repeat(0,2)['-' >> repeat(3)[alpha]] >> !alnum];

        script %= hold[repeat(4)[alpha] >> !alnum];

        region %= hold[(repeat(2)[alpha] >> !alnum)]   // ISO-3166-1 code
                | (repeat(3)[digit] >> !alnum);  // UN M.49 code

        variant %= hold[(repeat(5, 8)[alnum] >> !alnum)]
                 | ((digit >> repeat(3)[alnum]) >> !alnum);

        extension %= singleton >> repeat(1, inf)['-' >> hold[repeat(2, 8)[alnum]]];

        singleton %= digit | char_('a', 'w') | char_('y', 'z');

        privateuse %= 'x' >> repeat(1, inf)['-' >> repeat(1, 8)[alnum]];
    }

    qi::rule<Iterator, ietf_tag()> tag;
    qi::rule<Iterator, ietf_tag()> langtag;

    qi::rule<Iterator, std::string()> language;
    qi::rule<Iterator, std::string()> extlang;
    qi::rule<Iterator, std::string()> script;
    qi::rule<Iterator, std::string()> region;
    qi::rule<Iterator, std::string()> variant;
    qi::rule<Iterator, ietf_extension_entry()> extension;
    qi::rule<Iterator, char()> singleton;
    qi::rule<Iterator, std::vector<std::string>()> privateuse;
};

template<typename ConstIter>
bool parse_ietf_tag(ConstIter begin, ConstIter end, ietf_tag& result)
{
    using qi::parse;

    static const ietf_language_tag_grammar<ConstIter> grammar;

    result = ietf_tag();
    bool r = parse(begin, end, grammar, result);

    if (begin != end)
    {
        return false;
    }
    return r;

}

void print_tag(const ietf_tag& tag)
{
    std::cout << "Language: " << tag.language << '\n';

    if (!tag.script.empty())
    {
        std::cout << "Script: " << tag.script << '\n';
    }

    if (!tag.region.empty())
    {
        std::cout << "Region: " << tag.region << '\n';
    }

    if (!tag.variants.empty())
    {
        std::cout << "Variants:";
        for(const std::string& variant : tag.variants)
        {
            std::cout << ' ' << variant;
        }
        std::cout << '\n';
    }

    for (const ietf_extension_entry& ext : tag.extensions)
    {
        std::cout << "Extension '" << ext.extension_name << "' :";
        for(const std::string& ext_value : ext.extension_values)
        {
            std::cout << ' ' << ext_value;
        }
        std::cout << '\n';
    }

    if (!tag.private_use.empty())
    {
        std::cout << "Private Use:";
        for(const std::string& private_entry : tag.private_use)
        {
            std::cout << ' ' << private_entry;
        }
        std::cout << '\n';
    }
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
        "zh-CN-a-myext-more-x-private",
        "abcdefgh"
    };

    ietf_tag result;

    for (const std::string& input : inputs)
    {
        std::cout << input << '\n';

        bool valid_tag = parse_ietf_tag(input.begin(), input.end(), result);

        if (valid_tag)
        {
            print_tag(result);
        }
        else
        {
            std::cout << "Not a valid tag\n";
        }
        std::cout << '\n';
    }

    return EXIT_SUCCESS;
}
