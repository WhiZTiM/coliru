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

static auto const null_ = "null" >> qi::attr (null {});

static auto const bool_ =
  "true" >> qi::attr (true) | "false" >> qi::attr (false);

#if 0
static auto const text_   =
  '"' >> qi::raw [*('\\' >> qi::char_ | ~qi::char_('"'))] >> '"';
#endif

template <typename It, typename Skipper = qi::space_type>
struct grammar : qi::grammar<It, value (), Skipper>
{
  grammar () : grammar::base_type (value_)
  {
    using namespace qi;
    
    text_   = '"' >> qi::raw [*('\\' >> qi::char_ | ~qi::char_('"'))] >> '"';
    
    value_  = null_ | bool_ | text_ | double_ | object_ | array_;
    member_ = text_ >> ':' >> value_;
    object_ = '{' >> -(member_ % ',') >> '}';
    array_  = '[' >> -(value_ % ',') >> ']';
    
    BOOST_SPIRIT_DEBUG_NODES((value_)(member_)(object_)(array_))
  }
  
private:
  qi::rule<It, std::string ()> text_;
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
    
    data_
      %= eps [ _a = px::val (nullptr) ]
      > '{' > (
          kwd ( lit ("\"type\"" ) ) [ ':' >> parsed_type_ (_a) >> ',' ]
        / kwd ( lit ("\"value\"") ) [ ':' >> value_ (_a)       >> ',' ]
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
  qi::rule<It, data (), Skipper> start;
  
  qi::rule<It, data (), qi::locals<value_rule_type *>, Skipper> data_;
  
  qi::symbols<char, value_rule_type *> value_selector;
  
  qi::rule<It, int_1  (), Skipper> int1_parser;
  qi::rule<It, int_2a (), Skipper> int2a_parser;
  qi::rule<It, int_2b (), Skipper> int2b_parser;
  
  value_rule_type int1_rule, int2a_rule, int2b_rule;
  
  qi::rule<It, std::string (value_rule_type *&)         > parsed_type_;
  qi::rule<It, any_value   (value_rule_type *&), Skipper> value_;
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
       mine = mine::parse(sample2); std::cout << mine << '\n';
       mine = mine::parse(sample3); std::cout << mine << '\n';
       // mine = mine::parse(sample4); std::cout << mine << '\n';
  return 0;
}