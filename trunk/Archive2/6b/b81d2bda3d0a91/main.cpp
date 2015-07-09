#include <boost/spirit/include/qi.hpp>

    namespace qi = boost::spirit::qi;

    int main()
    {
        std::string const line = "/90pv-rksj-ucs2c usecmap";

        auto first = line.begin(), last = line.end();

        std::string label, token;
        bool ok = qi::phrase_parse(
                first, last, 
                qi::lexeme [ "/" >> +qi::graph ] >> qi::lexeme[+qi::graph], qi::blank, label, token);

        if (ok)
            std::cout << "parse success: label='" << label << "', token='" << token << "'\n";
        else
            std::cout << "parse failed\n";

        if (first!=last)
            std::cout << "remaining unparsed input: '" << std::string(first, last) << "'\n";
    }
