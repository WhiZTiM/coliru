#define BOOST_SPIRIT_USE_PHOENIX_V3

#include <boost/optional.hpp>
#include <boost/variant.hpp>
#include <boost/variant/recursive_variant.hpp>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

#include <boost/fusion/adapted.hpp>
#include <boost/fusion/adapted/std_pair.hpp>

//beginning of PARSE_FROM_RANGE.HPP


namespace custom
{
    BOOST_SPIRIT_TERMINAL_EX(parse_from_range)
}

namespace boost { namespace spirit
{
    ///////////////////////////////////////////////////////////////////////////
    // Enablers
    ///////////////////////////////////////////////////////////////////////////

    template <typename T>
    struct use_directive<qi::domain
      , terminal_ex<custom::tag::parse_from_range                     // enables parse_from_range(range)[parser]
        , fusion::vector1<T> >
    > : mpl::true_ {};

    template <>                                     // enables *lazy* parse_from_range(range)[parser]
    struct use_lazy_directive<
        qi::domain
      , custom::tag::parse_from_range
      , 1 // arity
    > : mpl::true_ {};


}}

namespace custom
{
    template<typename Subject, typename Range>
    struct parse_from_range_directive: boost::spirit::qi::unary_parser<parse_from_range_directive<Subject,Range> >
    {
        typedef Subject subject_type;
        parse_from_range_directive(Subject const& subject_, Range const& range_)
          : subject(subject_), range(range_) {}

        template <typename Context, typename Iterator>
        struct attribute
        {
            typedef typename
                boost::spirit::traits::attribute_of<subject_type, Context, Iterator>::type
            type;
        };

        template <typename Iterator, typename Context
          , typename Skipper, typename Attribute>
        bool parse(Iterator& first, Iterator const& last
          , Context& context, Skipper const& skipper, Attribute& attr_) const
        {
            typename Range::iterator iter=range.begin(),end=range.end();
            return subject.parse(iter, end, context, skipper, attr_) && (iter==end);
        }

        template <typename Context>
        boost::spirit::info what(Context& context) const
        {
            return boost::spirit::info("parse_from_range", subject.what(context));

        }

        Subject subject;
        Range range;
    };
}

namespace boost { namespace spirit { namespace qi
{
    template <typename Range, typename Subject, typename Modifiers>
    struct make_directive<
        terminal_ex<custom::tag::parse_from_range, fusion::vector1<Range> >, Subject, Modifiers>
    {
        typedef custom::parse_from_range_directive<Subject, Range> result_type;

        template <typename Terminal>
        result_type operator()(
            Terminal const& term, Subject const& subject, unused_type) const
        {
            return result_type(subject, fusion::at_c<0>(term.args));
        }
    };
}}}


//end of PARSE_FROM_RANGE.HPP


namespace spirit = ::boost::spirit;
namespace qi = spirit::qi;
namespace px = ::boost::phoenix;

namespace mine {
  
struct int_1  { int_1 (int i) : i1 (i) {} int_1 () : i1 () {} int i1; };
struct int_2a { int i1, i2; };
struct int_2b { int i1, i2; };

using any_value = boost::variant<int_1, int_2a, int_2b>;

struct data { std::string type; any_value value; };

template <class C, class T> std::basic_ostream<C,T>&
operator<< (std::basic_ostream<C,T>& os, int_1 const& i)
{
  return os << "{int1:" << i.i1 << '}';
}

template <class C, class T> std::basic_ostream<C,T>&
operator<< (std::basic_ostream<C,T>& os, int_2a const& i)
{
  return os << "{int2a:" << i.i1 << ',' << i.i2 << '}';
}

template <class C, class T> std::basic_ostream<C,T>&
operator<< (std::basic_ostream<C,T>& os, int_2b const& i)
{
  return os << "{int2b:" << i.i1 << ',' << i.i2 << '}';
}
  
template <class C, class T> std::basic_ostream<C,T>&
operator<< (std::basic_ostream<C,T>& os, data const& d)
{
  return os << "{type=" << d.type << ",value=" << d.value << '}';
}

}

BOOST_FUSION_ADAPT_STRUCT(mine::int_1,  (int, i1) )
BOOST_FUSION_ADAPT_STRUCT(mine::int_2a, (int, i1) (int, i2) )
BOOST_FUSION_ADAPT_STRUCT(mine::int_2b, (int, i1) (int, i2) )
BOOST_FUSION_ADAPT_STRUCT(mine::data,(std::string,type)(mine::any_value,value))

namespace mine {
    

template <typename It, typename Skipper = qi::space_type>
struct grammar: qi::grammar<It, data (), Skipper>
{
  grammar () : grammar::base_type (start)
  {
    using namespace qi;

    int1_parser  =        int_                      ;
    int2a_parser = '[' >> int_ >> ',' >> int_ >> ']';
    int2b_parser = '[' >> int_ >> ',' >> int_ >> ']';
    
    int1_rule  = int1_parser;
    int2a_rule = int2a_parser;
    int2b_rule = int2b_parser;
    
    value_selector.add
      ( "\"int1\"",  &int1_rule  )
      ("\"int2a\"",  &int2a_rule )
      ("\"int2b\"",  &int2b_rule )
    ;
    
    start = data_.alias ();
    
    parsed_type_ %=  raw[value_selector [ _r1  = _1 ]];
    value_ = lazy (*_r1);
    store_value_ = raw[( '[' >> int_%',' >> ']' )| int_][_r1=_1]; //if your rules are really complex this could be a problem
    
    data_
      %= eps [ _rule = px::val (nullptr) ]
      > '{' >( 
              ( //if you find "type" first do the same you were doing
                lit ("\"type\"" )  >> ':' >> parsed_type_ (_rule) >> ',' >>
                lit ("\"value\"")  >> ':' >> value_ (_rule)       >> ','
              )
            |
              ( //else store the raw value iterator range and use it later to parse the value
                lit ("\"value\"") >> ':' >> store_value_(_range) >> ',' >>
                lit ("\"type\"" ) >> ':' >> parsed_type_ (_rule) >> ',' >>
                custom::parse_from_range(_range)[value_(_rule)]
              )
             )
      > '}'
     ;
    
    on_error<fail>(start,
                   px::ref(std::cout)
                   << "Error! Expecting "
                   << qi::_4
                   << " here: '"
                   << px::construct<std::string>(qi::_3, qi::_2)
                   << "'\n"
                   );

  }
  
private:
  using value_rule_type = qi::rule<It, any_value (), Skipper>;
  qi::rule<It, data (), Skipper> start;
  
  qi::rule<It, data (), qi::locals<value_rule_type *,boost::iterator_range<It> >, Skipper> data_;
  
  qi::symbols<char, value_rule_type *> value_selector;
  
  qi::rule<It, int_1  (), Skipper> int1_parser;
  qi::rule<It, int_2a (), Skipper> int2a_parser;
  qi::rule<It, int_2b (), Skipper> int2b_parser;
  
  value_rule_type int1_rule, int2a_rule, int2b_rule;
  
  qi::_a_type _rule;
  qi::_b_type _range;
  
  
  qi::rule<It, std::string (value_rule_type *&)         > parsed_type_;
  qi::rule<It, any_value   (value_rule_type *&), Skipper> value_;
  qi::rule<It, void (boost::iterator_range<It>&), Skipper> store_value_;
};  
  
template <typename Range,
typename It = typename boost::range_iterator<Range const>::type>
data parse(Range const& input)
{
  grammar<It> g;
  
  It first(boost::begin(input)), last(boost::end(input));
  data parsed;
  bool ok = qi::phrase_parse(first, last, g, qi::space, parsed);
  
  if (ok && (first == last))
    return parsed;
  
  throw std::runtime_error("Remaining unparsed: '" +
                           std::string(first, last) + "'");
}

}

static std::string const sample1 = R"(
{
  "type": "int1",
  "value": 111,
})";

static std::string const sample2 = R"(
{
  "type": "int2a",
  "value": [ 111, 222 ],
})";

static std::string const sample3 = R"(
{
  "type": "int2b",
  "value": [ 111, 333 ],
})";

static std::string const sample4 = R"(
{
  "value": 111,
  "type": "int1",
})";

static std::string const sample5 = R"(
{
  "value": [ 111, 555 ],
  "type": "int2a",
})";

int main()
{
  auto mine = mine::parse(sample1); std::cout << mine << '\n';
       mine = mine::parse(sample2); std::cout << mine << '\n';
       mine = mine::parse(sample3); std::cout << mine << '\n';
       mine = mine::parse(sample4); std::cout << mine << '\n';
       mine = mine::parse(sample5); std::cout << mine << '\n';
  return 0;
}