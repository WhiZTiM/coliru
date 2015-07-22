#define BOOST_SPIRIT_X3_DEBUG
#include <iostream>
#include <boost/spirit/home/x3.hpp>

namespace SO {
    namespace x3 = boost::spirit::x3;

    x3::symbols<char> const keyword = []{
        x3::symbols<char> kw;
        kw += "for","begin","end","function","while","break","switch";
        return kw;
    }();

    x3::rule<struct symbol_tag>      const symbol_     ("symbol");
    x3::rule<struct identifier_tag>  const identifier_ ("identifier");
    x3::rule<struct lvalue_list_tag> const lvalue_list_("lvalue_list");
    x3::rule<struct statements_tag>  const statements_ ("statements");
    x3::rule<struct rule_tag>        const rule_       ("rule");

    auto symbol      = x3::lexeme[x3::alnum >> *(x3::alnum | '_')];
    auto identifier  = (!(x3::lexeme[keyword >> !(x3::alnum | '_')]) >> symbol_);
    auto lvalue_list = identifier_ % ',';
    auto statements  = *identifier_;
    auto rule        = "function"
                     >> identifier_
                     >> ('(' > -lvalue_list_ > ')')
                     >> ("begin" > statements_ > "end")
                     ;

    BOOST_SPIRIT_DEFINE(
                symbol_      = symbol,
                identifier_  = identifier,
                lvalue_list_ = lvalue_list,
                statements_  = statements,
                rule_        = rule
            );
}

int main() {
    std::string const sample = "function a() begin return one end";
    auto f = sample.begin(), l = sample.end();

    bool ok = phrase_parse(f, l, SO::rule_, SO::x3::space);
    if (ok)
        std::cout << "Parse success\n";
    else
        std::cout << "Parse failed\n";

    if (f!=l)
        std::cout << "Remaining unparsed: '" << std::string(f,l) << "'\n";
}