
#include <boost/lexical_cast.hpp>
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/fusion/include/std_pair.hpp>

#include <iostream>
#include <iomanip>
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
    
    if (!parse(f, l, auto_, value)) {
        throw std::string("bad boy");
    }

    return value;
}

template <typename T>
struct strict_real_policies : ::boost::spirit::qi::real_policies<T>
{
    static bool const expect_dot = true;
   
    /*template <typename Iterator>
    static bool parse_dot(Iterator& start, Iterator const& end) {
        bool parsed = ::boost::spirit::qi::parse(start, end, ',');
        return parsed; 
    }*/
};

template<typename T>
T tutu(std::string const& str) {
    T value;

    ::boost::spirit::qi::real_parser<T, strict_real_policies<T> > parser;
    ::boost::spirit::qi::int_parser<T> int_parser;
    using boost::spirit::qi::parse;
    
    if(! parse(str.cbegin(), str.cend(), parser, value)
        || ! parse(str.cbegin(), str.cend(), int_parser, value) ) {
        //|| parse(str.cbegin(), str.cend(), ',')) {
        throw std::string("eat a cat");
    }
    
    return value;
}

template<typename T>
void print(std::string value)
{
    std::stringstream ssTata, ssTutu;
    T tataVal = 0;
    T tutuVal = 0;
    T blcVal = 0;
    bool tataValErr = false;
    bool tutuValErr = false;
    bool blcValErr  = false;
    bool diffErr    = false;
    bool bErr    = false;

    try {
        tataVal = tata<T>(value);
    } catch(...) {
        tataValErr = true;
    }

    try {
        tutuVal = tutu<T>(value);
    } catch(...) {
        tutuValErr = true;
    }

    try {
        blcVal = ::boost::lexical_cast<T>(value);
    } catch(...) {
        blcValErr = true;
    }

#define W std::setw(15)
#define SEP "---------------"
#define P(v) W << (v##Err == true?std::string("<error>"):[=](){std::stringstream ss; ss << v; return ss.str();}())
#define STA(b) W << (b?"ok":"nok")

    T diff = std::abs(blcVal - tutuVal);
    bool b = tutuValErr == blcValErr;
    std::cout 
        << W << value
        << P(tataVal)
        << P(tutuVal)
        << P(blcVal)
        << P(diff)
        << STA(b)
        << "\n"
        ;

}
///////////////////////////////////////////////////////////////////////////////
//  Main program
///////////////////////////////////////////////////////////////////////////////
int main()
{
    //std::locale::global(std::locale("de_DE.UTF-8"));

    print<double>(titi(6.2346374890000000));
    print<int>(titi(345835866));

    print<double>("345,40");
    std::cout 
        << W << SEP
        << W << SEP
        << W << SEP
        << W << SEP
        << W << SEP
        << W << SEP
        << "\n";
    std::cout 
        << W << "Value"
        << W << "tata"
        << W << "tutu"
        << W << "lexical_cast"
        << W << "diff."
        << W << "status."
        << "\n"
        ;
    std::cout 
        << W << SEP
        << W << SEP
        << W << SEP
        << W << SEP
        << W << SEP
        << W << SEP
        << "\n";
        
    print<double>("-1.");
    print<double>("1.0e10");
    print<double>("-1.3e23");
    print<double>("-1,45");
    print<double>("+1,45");
    print<double>("1.45");
    print<double>("+1.45");  // tutu OK, tata NOK
    print<double>("+");
    print<double>("+zdaij1.45");
    print<double>("toto");
    print<double>("123 123");
    print<double>("1'23");
    print<double>("1\"23");
    print<double>("é\"'(-è_çà)");
    print<double>("&\"'(-è_çà)");
    print<double>("&é'(-è_çà)");
    print<double>("&é\"(-è_çà)");
    print<double>("&é\"'-è_çà)");
    print<double>("&é\"'(è_çà)");
    print<double>("&é\"'(-_çà)");
    print<double>("&é\"'(-èçà)");
    print<double>("&é\"'(-è_à)");
    print<double>("&é\"'(-è_ç)");
    print<double>("&é\"'(-è_çà");
    return 0;
}
