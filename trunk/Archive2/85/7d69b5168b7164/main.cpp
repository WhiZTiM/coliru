#define BOOST_SPIRIT_DEBUG
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/adapted/struct.hpp>
#include <boost/shared_ptr.hpp>
#include <sstream>

namespace qi = boost::spirit::qi;

struct parseContext {
    std::string encoding_;
    uint64_t    handId_;
};

BOOST_FUSION_ADAPT_STRUCT(parseContext, (std::string, encoding_)(uint64_t,handId_))

typedef boost::shared_ptr<parseContext> parseContextShPtr;

template <typename Iterator>
struct parseGrammar : qi::grammar<Iterator, parseContext()> {
    parseGrammar() : parseGrammar::base_type(ruleStart_)
    {
        ruleStart_      = ruleEncoding_ >> ruleHandHeader_;
        ruleEncoding_   = "ABC";
        ruleHandId_     = qi::long_long;
        ruleHandHeader_ = "DEF XYZ #" >> ruleHandId_;

        BOOST_SPIRIT_DEBUG_NODES((ruleStart_)(ruleEncoding_)(ruleHandId_)(ruleHandHeader_))
    }

    // Rules
    qi::rule<Iterator, parseContext()> ruleStart_;
    qi::rule<Iterator, std::string()> ruleEncoding_;
    qi::rule<Iterator, uint64_t()> ruleHandId_, ruleHandHeader_;
};

void test()
{
    std::stringstream sb("ABCDEF XYZ #555: PQI #777");
    sb.unsetf(std::ios::skipws);

    typedef boost::spirit::istream_iterator It;
    const parseGrammar<It> p;
    It b(sb), e;

    parseContextShPtr ctx(new parseContext);
    bool r = qi::parse(b, e, p, *ctx);
    if (r) {
        std::cout << "Success: " << ctx->encoding_ << ", " << ctx->handId_ << std::endl;
    }

    else {
        std::cout << "Failure" << std::endl;
    }

    if (b!=e)
        std::cout << "Remaining: '" << std::string(b, e).substr(0, 32) << "'...\n";
}

int main()
{
    test();
}
