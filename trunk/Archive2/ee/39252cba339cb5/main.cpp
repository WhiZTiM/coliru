
#include <boost/lexical_cast.hpp>
//#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/phoenix.hpp>



#include <cstdint>
#include <iostream>
#include <iomanip>
#include <string>
#include <locale>
#include <type_traits>

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

template< typename T >
struct Parser{

    template< typename Iterator>
        static bool parse(Iterator &f, Iterator &l, T &value)
        {
            using boost::spirit::qi::parse;
            using boost::spirit::qi::auto_;
            return parse(f, l, auto_, value) && f == l;
        }
};

template<>
struct Parser<bool>{
    template< typename Iterator >
        static bool parse(Iterator &f, Iterator &l, bool &value)
        {
            using boost::spirit::qi::parse;
            using boost::spirit::qi::auto_;
            using boost::spirit::qi::lit;
            auto parser = boost::spirit::qi::auto_
                | (
                   boost::spirit::qi::lit("0")[ boost::spirit::qi::_val = false ]
                   | boost::spirit::qi::lit("1")[ boost::spirit::qi::_val = true ]
                  );
            return parse(f, l, parser, value) && f == l;
        }
};

template <typename T>
T tata(std::string const &str)
{
    T value;
    
    auto f(str.cbegin());
    auto l(str.cend());
    
    if (!Parser<T>::parse(f, l, value) || f != l) {
        throw std::string("bad boy");
    }

    return value;
}


template<typename T>
int print(std::string value, std::string name = "")
{
    std::stringstream ssTata
      //,ssTutu
      ;
    T tataVal = 0;
    //T tutuVal = 0;
    T blcVal = 0;
    bool tataValErr = false;
    //bool tutuValErr = false;
    bool blcValErr  = false;
    bool diffErr    = false;
    bool bErr    = false;

    try {
        tataVal = tata<T>(value);
    } catch(...) {
        tataValErr = true;
    }

    //try {
    //    tutuVal = tutu<T>(value);
    //} catch(...) {
    //    tutuValErr = true;
    //}
    
    try {
        blcVal = ::boost::lexical_cast<T>(value);
    } catch(...) {
        blcValErr = true;
    }

#define W std::setw(22)
#define SEP "----------------------"
#define P(v) W << (v##Err == true?std::string("<error>"):[=](){std::stringstream ss; ss << v; return ss.str();}())
#define Q(v) W << v
#define STA(b) W << (b?"ok":"nok")

    T diff = blcVal - tataVal;
    bool b = tataValErr == blcValErr;
    std::cout 
        << W << value
        << P(blcVal)
        << P(tataVal)
        //<< P(tutuVal)
        << P(diff)
        << STA(b)
        << Q(name)
        << "\n"
        ;
        
    return b ? 0 : 1;

}

template < typename T >
void test( std::string const &name )
{
    std::cout << name << "\n";
    
    std::cout 
        << W << SEP
        << W << SEP
        << W << SEP
      // << W << SEP
        << W << SEP
        << W << SEP
        << W << SEP
        << "\n";
    std::cout 
        << W << "Value"
        << W << "lexical_cast"
        << W << "tata"
        //<< W << "tutu"
        << W << "diff."
        << W << "status."
        << "\n";
    std::cout 
        << W << SEP
        << W << SEP
        << W << SEP
       // << W << SEP
        << W << SEP
        << W << SEP
        << W << SEP
        << "\n";
        
    {
    std::stringstream limits;
    limits << std::numeric_limits< T >::max();
    print< T >(limits.str(), "max");
    }
    
    {
    std::stringstream limits;
    limits << std::numeric_limits< T >::min();
    print< T >(limits.str(), "min");
    }
    
    print< T >("-1.");
    
    print< T >("1.0e10");
    print< T >("-1.3e23");
    print< T >("1.45");
    print< T >("+1.45");
    print< T >("0");
    print< T >("1");
    print< T >("1987651432");
    print< T >("4294967295");
    print< T >("4294967296");
    print< T >("-4294967296");
    print< T >("18446744073709551615");
    print< T >("18446744073709551616");

    print< T >("0.");
    print< T >("1.");
    print< T >("1,");
    print< T >("-0.");
    print< T >("+0.");
    print< T >("0.264");
    print< T >(".274");
    print< T >("-.274");
    print< T >("+.274");
    print< T >("235620.264");
    print< T >("234567890.9874651342");
    
    print< T >(".");
    print< T >("234.567.2");
    print< T >("");
    print< T >("¤");
    print< T >("²");
    print< T >("-");
    print< T >("+");
    print< T >("+zdaij1.45");
    print< T >("toto");
    print< T >("123 123");
    print< T >("1'23");
    print< T >("1\"23");
    print< T >("-1,45");
    print< T >("+1,45");

    print< T >("true");
    print< T >("false");
    print< T >("on");
    print< T >("off");
    
    print< T >("&\"'(-è_çà)");

    print< T >("-inf");
    print< T >("+inf");
    print< T >("inf");
    print< T >("-infinity");
    print< T >("+infinity");
    print< T >("nan");
    print< T >("NaN");
}

///////////////////////////////////////////////////////////////////////////////
//  Main program
///////////////////////////////////////////////////////////////////////////////
int main()
{
    std::cout << "boost version:" << BOOST_LIB_VERSION << "\n" ;   
    
    test< long double >("long double");
    test< double >("double");
    test< float >("float");
    test< uint8_t  >("uint8_t ");
    test< uint16_t >("uint16_t");
    test< uint32_t >("uint32_t");
    test< uint64_t >("uint64_t");
    test< int8_t  >("int8_t ");
    test< int16_t >("int16_t");
    test< int32_t >("int32_t");
    test< int64_t >("int64_t");
    test< bool >("bool");

    
    return 0;
}
