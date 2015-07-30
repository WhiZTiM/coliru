
#include <boost/lexical_cast.hpp>
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/fusion/include/std_pair.hpp>

#include <iostream>
#include <string>
#include <locale>


    template <typename OutputIterator, typename ValueType>
    bool toto(OutputIterator sink, ValueType d)
    {
        using boost::spirit::karma::auto_;
        using boost::spirit::karma::generate;

        return generate(sink, auto_ ,d );
    }

template <typename T>
std::string titi(T value)
{
    std::string generated;
    std::back_insert_iterator<std::string> sink(generated);
    if (!toto(sink, value)) {
        throw std::string("bad boy");
    }
    return generated;
}


template <typename T>
T tata(std::string const &str)
{
    using boost::spirit::qi::phrase_parse;
    using boost::spirit::qi::parse;
    using boost::spirit::qi::auto_;
    using boost::spirit::qi::_1;
    using boost::phoenix::ref;

    T value;
    
    char const* f(str.c_str());
    char const* l(f + strlen(f));
    //if (!phrase_parse(f, l, auto_[  ref(value) = _1 ]))
    
    if (parse(f, l, auto_, value )) {
        while (parse(f, l, ',')){
            throw std::string("bad boy");
        }
    } else {
        throw std::string("bad boy");
    }

    return value;
}

template <typename T>
struct strict_real_policies : ::boost::spirit::qi::real_policies<T>
{
    static bool const expect_dot = true;
    
    /*template <typename Iterator>
    static bool parse_dot(Iterator&, Iterator const&)
    {
        return false;
    }*/
};

template<typename T>
T tutu(std::string const& str)
{
    T value;
    
    typedef strict_real_policies<T> P;
    ::boost::spirit::qi::real_parser<T, P> parser;
    using boost::spirit::qi::auto_;


    if(! ::boost::spirit::qi::parse(str.cbegin(), str.cend(), parser, value))
    {
        throw std::string("eat a cat");
    }
    
    return value;
}


template<typename T>
void print(std::string value)
{
    std::stringstream ss;
    
    try {
        T val= tutu<T>(value);
        ss << val;
    } catch(...) {
        ss << "<error>";
    }
    
    std::string lcValue = ss.str();
    std::string space(15 - lcValue.size(), ' ');
    
    try {
        T val = ::boost::lexical_cast<T>(value);
        std::cout << lcValue << space << val << "\n";
    } catch(...) {
        std::string err = "<error>";
        std::cout << lcValue << space << err << "\n";
    }   
}
///////////////////////////////////////////////////////////////////////////////
//  Main program
///////////////////////////////////////////////////////////////////////////////
int main()
{
    //std::locale::global(std::locale("de_DE.UTF-8"));

    std::cout << titi(60000000) << "\n";
    std::cout << titi((double)6.2346374890000000) << "\n";
    std::cout << std::to_string(3457835866.2346374890000000) << "\n";
    std::cout << titi(boost::lexical_cast< double >( "1.345" )) << "\n";
    std::cout << "-------------------------" << "\n";
    print<double>(titi(6.2346374890000000));
    print<int>(titi(345835866));
    print<double>(std::to_string(3457835866.2346374890000000));
    print<double>("3457835866.2346374890000000");
    print<double>("345,40");
    std::cout << "-------------------------" << "\n";
    print<double>("-1.");
    print<double>("1.0e10");
    print<double>("-1.3e23");
    print<double>("-1,45");
    print<double>("+1,45");
    print<double>("1.45");
    print<double>("+1.45");  // tutu OK, tata NOK
    std::cout << "-------------------------" << "\n";
    
    return 0;
}
