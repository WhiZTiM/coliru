//#define BOOST_SPIRIT_DEBUG
#include <boost/fusion/adapted.hpp>
#include <boost/spirit/include/qi.hpp>
#include <map>
#include <string>
#include <vector>

// Structure stores the parsed command line information:
struct CmdData
{
    typedef std::string               Name;

    typedef std::string               ArgName;
    typedef std::string               Value;

    typedef std::vector<Value>        Values;  // Type defines a list of values:
    typedef std::map<ArgName, Values> Args;    // Type defines a map storing the relation between a argument and the corresponding values:

    Name cmd; // Stores the command name as a string.
    Args arg; // Stores the arguments and the corresponding values as strings.
};

BOOST_FUSION_ADAPT_STRUCT(CmdData, cmd, arg)

namespace Grammar
{
    namespace qi = boost::spirit::qi;

    // This class implements the grammar used to parse a command line.
    // The expected format is as follows:
    // - command
    // - command value0 ... valueN
    // - command -arg0 ... -argN
    // - command -arg0 value0 ... valueN ... -argN value0 ... valueN
    template <typename It>
    struct decode : qi::grammar<It, CmdData()>
    {
        decode() : decode::base_type(data)
        {
            using namespace qi;

            token  = +~char_("\r\n -");
            values = +token;

            //
            entry  = (lexeme['-' >> token] >> -values | attr("empty") >> values);
            args   = *entry;

            //
            data   = skip(qi::blank) [ token >> args ];

            BOOST_SPIRIT_DEBUG_NODES( (token)(values)(entry)(args)(data) )
        }

      private:
        qi::rule<It, CmdData()> data;

        // The following variables define the rules used within this grammar:
        typedef std::pair<CmdData::ArgName, CmdData::Values> Entry;
        qi::rule<It, CmdData::Values(), qi::blank_type> values;
        qi::rule<It, Entry(),           qi::blank_type> entry;
        qi::rule<It, CmdData::Args(),   qi::blank_type> args;

        // lexemes
        qi::rule<It, std::string()> token;
    };

}   // namespace

bool parse(const std::string& in)
{
    CmdData data;

    // Create an instance of the used grammar:
    using Gr = Grammar::decode<std::string::const_iterator>;
    Gr gr;

    // Try to parse the data stored within the stream according the grammar and store the result in the tag variable:
    auto f = in.begin(), l = in.end();
    bool b = boost::spirit::qi::parse(f, l, gr, data);

    std::cout << "Parsing: '" << in << "' ok: " << std::boolalpha << b << "\n";
    if (b)
        std::cout << "Entries parsed: " << data.arg.size() << "\n";
    if (f!=l)
        std::cout << "Remaining unparsed: '" << std::string(f,l) << "'\n";

    return b;
}

int main()
{
    parse("   cmd0");
    parse("   cmd0  -23.0 value0  value1  value2");
    parse("   cmd0  -arg0  -arg1  -arg2");
    parse("   cmd0  -arg0  value0  -arg1  value0  value1  -arg2  value0  value1  value2");
}

