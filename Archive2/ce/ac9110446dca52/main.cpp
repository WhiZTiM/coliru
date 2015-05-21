#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/variant/recursive_wrapper.hpp>
#include <boost/spirit/repository/include/qi_distinct.hpp>

namespace qi    = boost::spirit::qi;
namespace phx   = boost::phoenix;
namespace qr    = boost::spirit::repository::qi;

struct op_or  {};
struct op_and {};
struct op_xor {};
struct op_not {};

typedef std::string var;
template <typename tag> struct binop;
template <typename tag> struct unop;

typedef boost::variant<var,
        boost::recursive_wrapper<unop <op_not> >,
        boost::recursive_wrapper<binop<op_and> >,
        boost::recursive_wrapper<binop<op_xor> >,
        boost::recursive_wrapper<binop<op_or> >
        > expr;

        template <typename tag> struct binop
{
    explicit binop(const expr& l, const expr& r) : oper1(l), oper2(r) { }
    expr oper1, oper2;
};

template <typename tag> struct unop
{
    explicit unop(const expr& o) : oper1(o) { }
    expr oper1;
};
struct printer : boost::static_visitor<void>
{
    printer(std::ostream& os) : _os(os) {}
    std::ostream& _os;


    void operator()(const var& v) const { _os << v; }

    void operator()(const binop<op_and>& b) const { print(" & ", b.oper1, b.oper2); }
    void operator()(const binop<op_or >& b) const { print(" | ", b.oper1, b.oper2); }
    void operator()(const binop<op_xor>& b) const { print(" ^ ", b.oper1, b.oper2); }

    void print(const std::string& op, const expr& l, const expr& r) const
    {
        _os << "(";
        boost::apply_visitor(*this, l);
        _os << op;
        boost::apply_visitor(*this, r);
        _os << ")";
    }

    void operator()(const unop<op_not>& u) const
    {
        _os << "(";
        _os << "!";
        boost::apply_visitor(*this, u.oper1);
        _os << ")";
    }
};

std::ostream& operator<<(std::ostream& os, const expr& e)
{ boost::apply_visitor(printer(os), e); return os; }

template <typename It, typename Skipper = qi::space_type>
struct parser : qi::grammar<It, expr(), Skipper>
{
    parser() : parser::base_type(expr_)
    {
        using namespace qi;

        expr_  = or_.alias();

        or_  = xor_ [_val = _1] >> *((qr::distinct(alnum|'_')["or"]  >> xor_ ) [ _val = phx::construct<binop<op_or >>(_val, _1) ]) | xor_ [ _val = _1 ];
        xor_ = and_ [_val = _1] >> *((qr::distinct(alnum|'_')["xor"] >> and_) [ _val = phx::construct<binop<op_xor>>(_val, _1) ]) | and_   [ _val = _1 ];
        and_ = not_ [_val = _1] >> *((-qr::distinct(alnum|'_')["and"] >> not_) [ _val = phx::construct<binop<op_and>>(_val, _1) ]) | not_ [ _val = _1 ];
        not_ = (qr::distinct(alnum|'_')["not"] > simple) [ _val = phx::construct<unop <op_not>>(_1)] | simple [ _val = _1 ];

        simple = (('(' > expr_ > ')') | var_);
        var_ = qi::lexeme[!((lit("or")|lit("xor")|lit("and")|lit("not")) >> ' ') >> alpha >> *((alnum | char_("_")))];

        BOOST_SPIRIT_DEBUG_NODE(expr_);
        BOOST_SPIRIT_DEBUG_NODE(or_);
        BOOST_SPIRIT_DEBUG_NODE(xor_);
        BOOST_SPIRIT_DEBUG_NODE(and_);
        BOOST_SPIRIT_DEBUG_NODE(not_);
        BOOST_SPIRIT_DEBUG_NODE(simple);
        BOOST_SPIRIT_DEBUG_NODE(var_);
    }

    private:
    qi::rule<It, var() , Skipper> var_;
    qi::rule<It, expr(), Skipper> not_, and_, xor_, or_, simple, expr_;
};

int main()
{
    for (auto& input : std::list<std::string> {
            // From the OP:
            "(a and b) xor ((c and d) or (a and b));",
            "a and b xor (c and d or a and b);",
            "a b;",
            "a b or c;",
            /// Simpler tests:
            "a and b;",
            "a or b;",
            "a xor or_1;",
            "not a;",
            "not a and b;",
            "not (a and b);",
            "a or b or c;",
            })
    {
        auto f(std::begin(input)), l(std::end(input));
        parser<decltype(f)> p;

        try
        {
            expr result;
            bool ok = qi::phrase_parse(f,l,p > ';',qi::space,result);

            if (!ok)
                std::cerr << "invalid input\n";
            else
                std::cout << "result: " << result << "\n";

        } catch (const qi::expectation_failure<decltype(f)>& e)
        {
            std::cerr << "expectation_failure at '" << std::string(e.first, e.last) << "'\n";
        }

        if (f!=l) std::cerr << "unparsed: '" << std::string(f,l) << "'\n";
    }
    return 0;
}

