#include <boost/spirit/home/x3.hpp>
#include <iostream>

int main() {
    namespace x3 = boost::spirit::x3;

    x3::symbols<char> keyword;
    keyword += "for","begin","end","function","while","break","switch";

    static auto symbol      = x3::lexeme[x3::alnum >> *(x3::alnum | '_')];
    static auto identifier  = (!(x3::lexeme[keyword >> !(x3::alnum | '_')]) >> symbol);
    static auto lvalue_list = identifier % ',';
    static auto statements  = *identifier;
    static auto rule        = "function"
                            >> identifier
                            >> ('(' > lvalue_list > ')')
                            >> ("begin" > statements > "end")
                            ;

    std::string const sample = "function a() begin return one end";
    auto f = sample.begin(), l = sample.end();

    try {
        bool ok = phrase_parse(f, l, rule, x3::space);
        if (ok)
            std::cout << "Parse success\n";
        else
            std::cout << "Parse failed\n";
    } catch(x3::expectation_failure<std::string::const_iterator> const& e) {
        std::cerr << e.what() << " at position #" << std::distance(sample.begin(), e.where()) << "\n";
    };

    if (f!=l)
        std::cout << "Remaining unparsed: '" << std::string(f,l) << "'\n";
}

