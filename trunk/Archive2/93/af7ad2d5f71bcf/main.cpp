#define BOOST_SPIRIT_USE_PHOENIX_V3

#include <boost/optional.hpp>
#include <boost/variant.hpp>
#include <boost/variant/recursive_variant.hpp>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

#include <boost/spirit/repository/include/qi_kwd.hpp>
#include <boost/spirit/repository/include/qi_keywords.hpp>

#include <boost/fusion/adapted.hpp>
#include <boost/fusion/adapted/std_pair.hpp>

namespace spirit = ::boost::spirit;
namespace qi = spirit::qi;
namespace px = ::boost::phoenix;
namespace proto = ::boost::proto;

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

namespace json {
  
struct null {
  constexpr bool operator== (null) const { return true; }
};

template<typename Ch, typename Tr>
std::basic_ostream<Ch, Tr>&
operator<< (std::basic_ostream<Ch, Tr>& os, null) { return os << "null"; }

using text = std::string;

using value = boost::make_recursive_variant<
    null
  , text                                        // string
  , double                                      // number
  , std::map<text, boost::recursive_variant_>   // object
  , std::vector<boost::recursive_variant_>      // array
  , bool
>::type;

using member = std::pair<text, value>;
using object = std::map<text, value>;
using array = std::vector<value>;

static auto const null_ = proto::deep_copy ("null" >> qi::attr (null {}));

static auto const bool_ =
  proto::deep_copy ("true" >> qi::attr (true) | "false" >> qi::attr (false));
  
static auto const text_ = proto::deep_copy (
  '"' >> qi::raw [*('\\' >> qi::char_ | ~qi::char_('"'))] >> '"');

template <typename It, typename Skipper = qi::space_type>
struct grammar : qi::grammar<It, value (), Skipper>
{
  grammar () : grammar::base_type (value_)
  {
    using namespace qi;   
    value_  = null_ | bool_ | text_ | double_ | object_ | array_;
    member_ = text_ >> ':' >> value_;
    object_ = '{' >> -(member_ % ',') >> '}';
    array_  = '[' >> -(value_ % ',') >> ']';
    
    BOOST_SPIRIT_DEBUG_NODES((value_)(member_)(object_)(array_))
  }
  
private:
  qi::rule<It, json:: value (), Skipper> value_;
  qi::rule<It, json::member (), Skipper> member_;
  qi::rule<It, json::object (), Skipper> object_;
  qi::rule<It, json:: array (), Skipper> array_;
};

template <typename Range,
  typename It = typename boost::range_iterator<Range const>::type>
value parse(Range const& input)
{
  grammar<It> g;
  
  It first(boost::begin(input)), last(boost::end(input));
  value parsed;
  bool ok = qi::phrase_parse(first, last, g, qi::space, parsed);
  
  if (ok && (first == last))
    return parsed;
  
  throw std::runtime_error("Remaining unparsed: '" +
                           std::string(first, last) + "'");
}
  
} // namespace json

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
    using spirit::repository::qi::kwd;
    
    _a_type _rule;
    _b_type _range;
    
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
    
    // parse json, returns raw iterator range.
    parse_as_json_ = raw [ json_ ] [ _r1 = _1 ];
    
    
    // parsed_type_ %=  raw[value_selector [ _r1  = _1 ]];
    parsed_type_ %=  raw[value_selector [ _r1  = _1 ]]
      >> -(  // if the range is not empty, parse it with _r1 grammar
             eps (_r2)
             > omit [ custom::parse_from_range (_r2) [ lazy (*_r1) ] ]
      )
    ;
    

    // if _r1 is not NULL then parse with it; otherwise parse as json
    value_ = ( eps (_r1) > lazy (*_r1) ) | parse_as_json_ (_r2);
    
    data_
      %= eps [ _rule = nullptr ]
      > '{' > (
          kwd ( lit ("\"type\"" ) ) [ ':' >> parsed_type_ (_rule, _range) >> ',' ]
        / kwd ( lit ("\"value\"") ) [ ':' >> value_ (_rule, _range)       >> ',' ]
      ) > '}'
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
  using range_type = ::boost::iterator_range<It>;
  
  qi::rule<It, data (), Skipper> start;
  
  qi::rule<It, data (), qi::locals<value_rule_type *, range_type>, Skipper> data_;
   
  qi::symbols<char, value_rule_type *> value_selector;
  
  qi::rule<It, int_1  (), Skipper> int1_parser;
  qi::rule<It, int_2a (), Skipper> int2a_parser;
  qi::rule<It, int_2b (), Skipper> int2b_parser;
  
  value_rule_type int1_rule, int2a_rule, int2b_rule;
  
  qi::rule<It, void (range_type&), Skipper> parse_as_json_;
  
  qi::rule<It, std::string (value_rule_type *&, range_type&)> parsed_type_;
  qi::rule<It, any_value   (value_rule_type *&, range_type&), Skipper> value_;
  
  json::grammar<It, Skipper> json_;
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
 
int main()
{
  auto mine = mine::parse(sample1); std::cout << mine << '\n';
       // mine = mine::parse(sample2); std::cout << mine << '\n';
       // mine = mine::parse(sample3); std::cout << mine << '\n';
       // mine = mine::parse(sample4); std::cout << mine << '\n';
  return 0;
}