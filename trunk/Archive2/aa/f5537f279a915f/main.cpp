#define BOOST_SPIRIT_USE_PHOENIX_V3
//#define BOOST_SPIRIT_DEBUG

#include <boost/fusion/adapted.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/repository/include/qi_distinct.hpp>
#include <boost/spirit/repository/include/qi_seek.hpp>
#include <boost/variant.hpp>

#include <cassert>

namespace phx = boost::phoenix;
namespace qi  = boost::spirit::qi;
namespace qr  = boost::spirit::repository::qi;

namespace Common {
    typedef std::string pp_sym;
}

namespace Ast {
    using Common::pp_sym;

    typedef std::string Str;
    typedef std::pair<Str, Str> Pair;
    typedef std::vector<Pair> Pairs;

    struct ConditionalBlock;

    namespace tag {
        struct define;
        struct undefine;
    }

    template <typename Tag> struct Directive {
        pp_sym name;
    };

    typedef Directive<tag::define> Define; 
    typedef Directive<tag::undefine> Undef; 

    typedef boost::make_recursive_variant<
                Pairs,
                boost::recursive_wrapper<ConditionalBlock>,
                Define,
                Undef
            >::type Block;

    typedef std::vector<Block> Blocks;

    struct ConditionalBlock {
        pp_sym required;
        Blocks if_, else_;
    };
}

BOOST_FUSION_ADAPT_TPL_STRUCT((Tag), (Ast::Directive)(Tag), name)
BOOST_FUSION_ADAPT_STRUCT(Ast::ConditionalBlock, required, if_, else_)

/***
 * Grammar definitions
 */

template <typename Iterator>
struct simple_grammar : qi::grammar<Iterator, Ast::Blocks()> {

    simple_grammar() : simple_grammar::base_type(start)
    {
        using namespace qi;
        using qr::distinct;
        using qr::seek;

        start   = skip(blank) [ blocks ];
        blocks  = *block;
        block   = define | undef | conditional_block | +pair; 

        pair      = +~char_("=\r\n") >> '=' >> *(char_ - eol) >> *eol;
        pp_symbol = qr::distinct(char_("A-Za-z_")) [ +char_("A-Za-z_") ];

        define = '#' >> distinct(alnum | '_') [ "define" ] >> pp_symbol >> seek[*eol];
        undef  = '#' >> distinct(alnum | '_') [ "undef"  ] >> pp_symbol >> seek[*eol];

        else_  = '#' >> distinct(alnum | '_') [ "else"   ] >> seek[*eol];
        endif  = '#' >> distinct(alnum | '_') [ "endif"  ] >> seek[*eol];

        conditional_block = 
            ('#' >> distinct(alnum | '_') [ "ifdef" ] >> pp_symbol >> seek[*eol])
            >> *(!(else_|endif) >> block) 
            >> -else_
            >> *(!endif >> block)
            >> endif
            ;

        BOOST_SPIRIT_DEBUG_NODES((start)(blocks)(block)(pair)(pp_symbol)(define)(undef)(else_)(endif)(conditional_block))
    }

private:
    using Skipper = qi::blank_type;

    qi::rule<Iterator, Ast::Blocks()> start;

    qi::rule<Iterator, Ast::Blocks(), Skipper> blocks;
    qi::rule<Iterator, Ast::Block(),  Skipper> block;

    // directive
    qi::rule<Iterator, Ast::ConditionalBlock(), Skipper> conditional_block;
    qi::rule<Iterator, Ast::Define(),           Skipper> define;
    qi::rule<Iterator, Ast::Undef(),            Skipper> undef;
    // empty directives
    qi::rule<Iterator, Skipper> else_, endif;

    // lexeme
    qi::rule<Iterator, Ast::Pair()>   pair;
    qi::rule<Iterator, Ast::pp_sym()> pp_symbol;
};

namespace Logic {
    using Common::pp_sym;
    
    typedef std::set<pp_sym> pp_syms;

    struct context {
        pp_syms defined;
    };

    struct Preprocess : boost::static_visitor<void> {
        context ctx;
        std::string indent;

        Preprocess(context ctx = {}, std::string indent = "") 
            : ctx(std::move(ctx)), indent(std::move(indent))
        { }

        void operator()(Ast::Blocks const& blocks) {
            for (auto& b : blocks)
                boost::apply_visitor(*this, b);
        }
        void operator()(Ast::Block const& block) {
            boost::apply_visitor(*this, block);
        }
        void operator()(Ast::Pairs const& pairs) {
            for (auto& p : pairs)
                std::cout << indent << p.first << "=" << p.second << "\n";
        }
        void operator()(Ast::ConditionalBlock const& cb) {
            bool const satisfied = ctx.defined.count(cb.required);

            auto old_indent = indent;
            indent += "\t";
            std::cout << old_indent << "#ifdef " << cb.required << " // " << std::boolalpha << satisfied << "\n";

            Preprocess isolated{ctx, indent+"// "}; // prevent changes to ctx to affect us for the non-matching branch
            
            (satisfied? *this : isolated)(cb.if_);
            std::cout << old_indent << "#else " << " // ifdef " << cb.required << "\n";
            (satisfied? isolated : *this)(cb.else_);

            std::cout << old_indent << "#endif " << " // ifdef " << cb.required << "\n";
            indent.resize(indent.size()-1);
        }
        void operator()(Ast::Define const& directive) {
            ctx.defined.insert(directive.name);

            std::cout << indent << "#define\t" << directive.name;
            report();
        }
        void operator()(Ast::Undef const& directive) {
            ctx.defined.erase(directive.name);

            std::cout << indent << "#undef\t" << directive.name;
            report();
        }

      private:
        void report() const {
            std::cout << "\t// effective: ";
            for (auto& sym : ctx.defined) std::cout << sym << " ";
            std::cout << "\n";
        }
    };

}

int main() {
    typedef boost::spirit::istream_iterator It;

    typedef simple_grammar<It> my_grammar;

    my_grammar gram; // Our grammar
    Ast::Blocks ast; // Our tree

    It it(std::cin >> std::noskipws), end;

    bool b = qi::parse(it, end, gram, ast);

    if (it != end)
        std::cout << "Remaining input: '" << std::string(it, end) << "'\n";

    assert(b);

    std::cout << "Preprocess results:\n\n";

    Logic::Preprocess pp({{"EXTERNAL"}} , "    ");
    pp(ast);

    std::cout << "\n\nDefines still in effect: ";
    for (auto& sym : pp.ctx.defined) std::cout << sym << " ";
}
