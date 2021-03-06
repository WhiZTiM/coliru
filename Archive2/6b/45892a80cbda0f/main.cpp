//#define BOOST_SPIRIT_DEBUG
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/repository/include/qi_distinct.hpp>
#include <boost/variant/recursive_wrapper.hpp>

namespace qi    = boost::spirit::qi;
namespace qr    = boost::spirit::repository::qi;
namespace phx   = boost::phoenix;

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

        or_  = (xor_ >>  qr::distinct(alnum|'_')[ "or" ]  >> or_ ) [ _val = phx::construct<binop<op_or >>(_1, _2) ] | xor_   [ _val = _1 ];
        xor_ = (and_ >>  qr::distinct(alnum|'_')[ "xor" ] >> xor_) [ _val = phx::construct<binop<op_xor>>(_1, _2) ] | and_   [ _val = _1 ];
        and_ = (not_ >> -qr::distinct(alnum|'_')[ "and" ] >> and_) [ _val = phx::construct<binop<op_and>>(_1, _2) ] | not_   [ _val = _1 ];
        not_ = (qr::distinct(alnum|'_')[ "not" ] > simple       )  [ _val = phx::construct<unop <op_not>>(_1)     ] | simple [ _val = _1 ];

        simple = (('(' > expr_ > ')') | var_);
        var_   = 
            !qr::distinct(alnum|'_') [ lit("or")|"xor"|"and"|"not" ] >>
            qr::distinct(alnum|'_') [ alpha >> *(alnum | char_("_")) ]
            ;

        BOOST_SPIRIT_DEBUG_NODES((expr_) (or_) (xor_) (and_) (not_) (simple) (var_))
    }

    private:
    qi::rule<It, var()> var_;
    qi::rule<It, expr(), Skipper> not_, and_, xor_, or_, simple, expr_;
};

int main()
{
    for (auto& input : std::list<std::string> {
#if 0
            "a or b or c;",
            "(a and b);",
            "a xor b;",
            "a or b;",
            "(a) or (b);",
            "((c and d) or (a and b));",
#endif
            "(a and b) xor ((c and d) or (a and b));",
            "(a b) xor ((c d) or (a b));",

            "a and b xor c and d or a and b;",
            "a b xor c d or a b;",

            /// Simpler tests:
            "a and b;",
            "a b;",
            "not a and b;",
            "not a b;",

            "not (a and b);",
            "not (a b);",
            })
    {
        auto f(std::begin(input)), l(std::end(input));
        parser<decltype(f)> p;

        try
        {
            expr result;
            bool ok = qi::phrase_parse(f,l,p > ';',qi::space,result);

            std::cout << "\n======= input '" << input << "'\n";

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
