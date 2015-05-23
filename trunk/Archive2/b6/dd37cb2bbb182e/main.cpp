#define BOOST_SPIRIT_DEBUG
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/pair.hpp>
#include <iostream>
#include <string>
#include <map>

typedef std::map<std::string, std::string> ARGTYPE;

namespace qi     = boost::spirit::qi;

template <typename It, typename Skipper>
struct NestedGrammar : qi::grammar <It, ARGTYPE(), Skipper>
{
    NestedGrammar() : NestedGrammar::base_type(Sequence)
    {
        using namespace qi;
        KeyName = qi::char_("a-zA-Z_") >> *qi::char_("a-zA-Z0-9_");
        Value = +qi::char_("-.a-zA-Z_0-9");

        Pair = KeyName >> -(
                '=' >> ('{' >> raw[Sequence] >> '}' | Value)
            );

        Sequence = Pair % char_(";&") >> -omit[char_(";&")];

        BOOST_SPIRIT_DEBUG_NODES((KeyName) (Value) (Pair) (Sequence))
    }
private:
    qi::rule<It, ARGTYPE(), Skipper> Sequence;
    qi::rule<It, std::string()> KeyName;
    qi::rule<It, std::string(), Skipper> Value;
    qi::rule<It, std::pair <std::string, std::string>(), Skipper> Pair;
};


template <typename Iterator>
ARGTYPE Parse2(Iterator begin, Iterator end)
{
    NestedGrammar<Iterator, qi::space_type> p;
    ARGTYPE data;
    qi::phrase_parse(begin, end, p, qi::space, data);
    return data;
}


// ARGTYPE is std::map<std::string,std::string>
void NestedParse(std::string Input, ARGTYPE& Output)
{
    Input.erase(std::remove_if(Input.begin(), Input.end(), isspace), Input.end());
    Output = Parse2(Input.begin(), Input.end());
}

int main()
{
    {
        ARGTYPE Out;

        std::string const Example1 = "Key1=Value1 ; Key2 = 01-Jan-2015; Key3 = 2.7181; Key4 = Johnny";
        NestedParse(Example1, Out);
        for (ARGTYPE::iterator i = Out.begin(); i != Out.end(); i++)
            std::cout << i->first << "|" << i->second << std::endl;

        /* get the following, as expected:
           Key1|Value1
           Key2|01-Jan-2015
           Key3|2.7181
           Key4|Johnny
           */
    }

    std::cout << "=====" << std::endl;

    {
        ARGTYPE Out;

        std::string const Example2 = "Key1 = Value1; Key2 = {InnerK1 = one; IK2 = 11-Nov-2011;};";
        NestedParse(Example2, Out);
        for (ARGTYPE::iterator i = Out.begin(); i != Out.end(); i++)
            std::cout << i->first << "|" << i->second << std::endl;

        /* get the following, as expected:
           Key1|Value1
           key2|InnerK1=one;IK2=11-Nov-2011
           */
    }
    std::cout << "=====" << std::endl;

    {
        ARGTYPE Out;

        std::string const Example3 = "K1 = V1; K2 = {IK1=IV1; IK2=IV2;}; K3=V3; K4 = {JK1=JV1; JK2=JV2;};";
        NestedParse(Example3, Out);
        for (ARGTYPE::iterator i = Out.begin(); i != Out.end(); i++)
            std::cout << i->first << "|" << i->second << std::endl;

        /* Only get the first two lines of the expected output:
           K1|V1
           K2|IK1=IV1;IK2=IV2
           K3|V3
           K4|JK1=JV1;JK2=JV2
           */
    }
}
