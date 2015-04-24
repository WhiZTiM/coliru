#include <boost/spirit/include/qi.hpp>

using namespace boost::spirit;

namespace parsernm { BOOST_SPIRIT_TERMINAL_EX(aparser); }

namespace boost { namespace spirit {
    
    template <>                     //enables aparser
    struct use_terminal<
        qi::domain
      , parsernm::tag::aparser
      > : mpl::true_
    {};
    
    template <typename A0>          //enables aparser(arg)
    struct use_terminal<
        qi::domain
      , terminal_ex<
            parsernm::tag::aparser
          , fusion::vector1<A0>
          >
      > : mpl::true_
    {};
}}

namespace parsernm
{
    struct aparser_impl : boost::spirit::qi::primitive_parser<aparser_impl>
    {
        aparser_impl(int _param=0)
          : param(_param)
        {}

        template <typename Iterator, typename Context, typename Skipper, typename Attribute>
        bool parse(Iterator& first, Iterator const& last, Context&,
                   Skipper const& skipper, Attribute& attr) const
        {
            return true;
        }

        template <typename Context>
        boost::spirit::info what(Context&) const {
            return boost::spirit::info("aparser");
        }

        int param;
    };
}

namespace boost { namespace spirit { namespace qi {
    template <typename Modifiers>
    struct make_primitive<parsernm::tag::aparser, Modifiers>
    {
        typedef parsernm::aparser_impl result_type;

        result_type operator()(unused_type, unused_type) const
        {
            return result_type();
        }
    };
    
    template <typename Modifiers, typename A0>
    struct make_primitive<
        terminal_ex<
            parsernm::tag::aparser
          , fusion::vector1<A0>
          >
      , Modifiers
      >
    {
        typedef parsernm::aparser_impl result_type;

        template <typename Terminal>
        result_type operator()(Terminal const& term, unused_type) const
        {
            return result_type(fusion::at_c<0>(term.args));
        }
    };
}}}

int main(int argc, char* argv[])
{
    std::string input("");
    std::string::iterator first = input.begin();
    qi::parse(first, input.end(), parsernm::aparser(10));
    qi::parse(first, input.end(), parsernm::aparser);

    return 0;
}
