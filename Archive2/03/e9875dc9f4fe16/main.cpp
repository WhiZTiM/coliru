
#include <cmath>
#include <cstdint>
#include <iomanip>
#include <limits>
#include <string>
#include <type_traits>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/phoenix.hpp>

#include <string>
#include <type_traits>

#include <iostream>
#include <exception>

#include <cassert>

#define CPPUNIT_ASSERT assert

#define CPPUNIT_ASSERT_EQUAL(exp, test) assert( exp == test )

/* #include <cppunit/extensions/HelperMacros.h> */

namespace fwLocale
{
    
namespace ut
{

class LocaleTest //: public CPPUNIT_NS::TestFixture
{
    //CPPUNIT_TEST_SUITE( LocaleTest );

    //CPPUNIT_TEST( longDoubleTest );
    //CPPUNIT_TEST( doubleTest );
    //CPPUNIT_TEST( floatTest );
    //CPPUNIT_TEST( charTest );
    //CPPUNIT_TEST( uint8Test );
    //CPPUNIT_TEST( uint16Test );
    //CPPUNIT_TEST( uint32Test );
    //CPPUNIT_TEST( uint64Test );
    //CPPUNIT_TEST( int8Test );
    //CPPUNIT_TEST( int16Test );
    //CPPUNIT_TEST( int32Test );
    //CPPUNIT_TEST( int64Test );
    //CPPUNIT_TEST( boolTest );
    //CPPUNIT_TEST( generateTest );

    //CPPUNIT_TEST_SUITE_END();

public:

    void longDoubleTest();
    void doubleTest();
    void floatTest();
    void charTest();
    void uint8Test();
    void uint16Test();
    void uint32Test();
    void uint64Test();
    void int8Test();
    void int16Test();
    void int32Test();
    void int64Test();
    void boolTest();

    void generateTest();
};

} // namespace ut

/*

 struct ValueCastException : std::exception
{
     const char* what() const noexcept;
};

 struct GenerateException : std::exception
{
     const char* what() const noexcept;
};

template <typename T>
typename std::enable_if< !std::is_floating_point< T >::value, bool>::type generate(T value, std::string& generated)
{
    std::back_insert_iterator<std::string> sink(generated);
    using boost::spirit::karma::auto_;
    using boost::spirit::karma::generate;
    return generate(sink, auto_, value);
}

template<typename T, int P>
struct double_policy : ::boost::spirit::karma::real_policies< T >
{
    static unsigned int precision(T)
    {
        return P;
    }
};

template <typename T>
typename std::enable_if< std::is_floating_point< T >::value, bool>::type generate(T value, std::string& generated)
{
    std::back_insert_iterator<std::string> sink(generated);
    using boost::spirit::karma::auto_;
    using boost::spirit::karma::generate;
    using boost::spirit::karma::real_generator;

    typedef real_generator<T, double_policy<T, 6>> PolicyType;
    return generate(sink, PolicyType(), value);
}


template <typename T>
std::string generate(T value)
{
    std::string generated;

    if(!generate(value, generated))
    {
        throw GenerateException();
    }

    return generated;
}


template< typename DestType, typename FromType >
struct Caster
{
    static bool cast(FromType &&str, DestType &value)
    {
        using boost::spirit::qi::parse;
        using boost::spirit::qi::auto_;

        auto f(std::begin(str));
        auto l(std::end(str));

        return parse(f, l, auto_, value) && f == l;
    }
};


template<typename FromType>
struct Caster<bool, FromType>
{
    static bool cast(FromType &&str, bool &value)
    {
        using boost::spirit::qi::parse;
        using boost::spirit::qi::auto_;
        using boost::spirit::qi::lit;

        auto f(std::begin(str));
        auto l(std::end(str));

        auto parser = boost::spirit::qi::auto_
            | (
                    boost::spirit::qi::lit("0")[ boost::spirit::qi::_val = false ]
                    | boost::spirit::qi::lit("1")[ boost::spirit::qi::_val = true ]
              );

        bool success = parse(f, l, parser, value) && (f == l || *f == '\0');
        return success;

    }
};

//int < 0 with unsigned ints
//float out of bound values
//bool 1 0 && true false


template <typename DestType, typename FromType>
bool valueCast(FromType &&src, DestType &value)
{
    return Caster<DestType, FromType>::cast(src, value);
}

template <typename DestType, typename FromType>
DestType valueCast(FromType &&src)
{
    DestType value;

    if (! valueCast(src, value))
    {
        throw ValueCastException();
    }

    return value;
}


namespace ut
{


//------------------------------------------------------------------------------

template< typename T, bool trait >
bool equals(T a, T b, const boost::integral_constant<bool, trait>&)
{
    return a == b;
}

// Adapted from https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
template< typename T >
bool equals(T a, T b, const boost::true_type&)
{
    if ( a == b
            || !( a != b  && a == b ) // test for NaN
            )
    {
        return true;
    }

    // Compute difference
    T diff = std::fabs(a - b);
    a = std::fabs(a);
    b = std::fabs(b);

    // Find largest value
    T largest = (b > a) ? b : a;

    return (diff <= largest * 1.e-6);
}


template< typename T >
bool testValue(std::string valueStr,
       bool exceptValueCastError,
       bool exceptLexicalCastError,
       bool exceptSameResult,
       T* value = nullptr)
{

    T castValue = T();
    bool valueCastError = !::fwLocale::valueCast< T >(valueStr, castValue);
    if (value && !valueCastError)
    {
        *value = castValue;
    }


    T lexicalCastValue = T();
    bool lexicalCastError = false;
    try
    {
        lexicalCastValue = ::boost::lexical_cast< T >(valueStr);
    }
    catch(...)
    {
        lexicalCastError = true;
    }

    bool sameResult = equals<T>(castValue, lexicalCastValue, ::boost::is_floating_point< T >() ) ;

    bool testResult = true;

    if(exceptValueCastError != valueCastError)
    {
        std::cout 
            << "test '" << valueStr 
            << "' -> " << typeid(T).name() 
            << " : Expected valueCast failure : " << exceptValueCastError 
            << ", failed : " << valueCastError 
            << "\n" ;

        testResult = false;
    }

    if(exceptLexicalCastError != lexicalCastError)
    {
        std::cout 
            << "test '" << valueStr 
            << "' -> " << typeid(T).name() 
            << " : Expected lexicalCast failure : " << exceptLexicalCastError 
            << ", failed : " << lexicalCastError 
            << "\n" ;

        testResult = false;
    }

    if( (valueCastError || lexicalCastError) )
    {
        if(exceptSameResult)
        {
            std::cout
                << "Error: '" << valueStr 
                << "' -> " << typeid(T).name() 
                << " : Same cast result was expected, but: " 
                << (valueCastError ? "castValue failed" : "")
                << ((valueCastError && lexicalCastError) ? " and " : " ")
                << (lexicalCastError ? "lexicalCast failed" : " ")
                << "\n" ;
            testResult = false;
        }
    }
    else if(exceptSameResult != sameResult)
    {
        std::cout 
            << "Error: '" << valueStr 
            << "' -> " << typeid(T).name() 
            << " : Expected same cast result : " << exceptSameResult 
            << ", got values : " << "castValue:" << castValue << "!=" << "lexicalCastValue:" << lexicalCastValue 
            << "\n" ;

        testResult = false;
    }

    if(!testResult)// XXX TODO ?
    std::cout << std::setw(18) << typeid(T).name() 
        << " testValue: "
        << std::setw(30) << valueStr
        << " " << (testResult?"OK    ":"FAILED")
        << std::setw(30) << castValue
        << " : (" << (valueCastError?"error":((sameResult&&!lexicalCastError)?"like lex.cast":"not like lex.cast"))

        << std::setw(70) << castValue
        << std::setw(70) << lexicalCastValue
        << ")\n";

    return testResult;
}

template< typename T,
    bool AtLeast32Bit = (sizeof(T) >= 4),
    bool AtLeast64Bit = (sizeof(T) >= 8) >
struct EqualsMin
{
    static bool Int32(T)
    {
        return false;
    }

    static bool Int64(T)
    {
        return false;
    }
};

template< typename T>
struct EqualsMin<T, true, false>
{
    static bool Int32(T value)
    {
        return equals<T>(value, static_cast<T>(-2147483647), ::boost::is_floating_point< T >() );
    }

    static bool Int64(T)
    {
        return false;
    }
};


template< typename T>
struct EqualsMin<T, true, true>
{
    static bool Int32(T value)
    {
        return equals<T>(value, static_cast<T>(-2147483647), ::boost::is_floating_point< T >() );
    }

    static bool Int64(T value)
    {
        return equals<T>(value, static_cast<T>(-9223372036854775807), ::boost::is_floating_point< T >() );
    }
};



template<
    typename RefType,
    typename T,
    bool GoodSize = (sizeof(T) >= sizeof(RefType) || std::is_floating_point<T>::value )
    >
struct LimitLowest
{
    static bool check(T)
    {
        return false;
    }
};

template< typename RefType >
struct LimitLowest<RefType, bool, true>
{
    static bool check(bool)
    {
        return false;
    }
};

template< typename RefType, typename T >
struct LimitLowest<RefType, T, true>
{
    static bool check(T value)
    {
        //        XXX REMOVEME
 //        std::cout  << typeid(RefType).name() << " : " << typeid(T).name() << " --- limit : " << value << ":" << static_cast<T>(std::numeric_limits<RefType>::lowest())
 //        << "   >>> " << equals(value,
 //                static_cast<T>(std::numeric_limits<RefType>::lowest()),
 //                ::boost::is_floating_point< T >() ) << "\n";

        return equals(value,
                static_cast<T>(std::numeric_limits<RefType>::lowest()),
                ::boost::is_floating_point< T >() );
    }
};



template< typename T >
void testType()
{
    bool isBool = std::is_same< bool, T >::value;
    bool isInt = std::is_integral<T>::value && !isBool;
    bool isInt8 = isInt && sizeof(T) == 1;
    bool isFloatingType = std::is_floating_point<T>::value;
    bool isSigned = std::is_signed< T >::value;

    CPPUNIT_ASSERT(testValue< T >("0", false, false, true));
    CPPUNIT_ASSERT(testValue< T >("1", false, false, true));
    CPPUNIT_ASSERT(testValue< T >("9", isBool, isBool, !isBool));

    // generic integers tests
    {
        bool errorExpected = isInt8 || isBool;
        CPPUNIT_ASSERT(testValue< T >("10", errorExpected, errorExpected, !errorExpected));
        CPPUNIT_ASSERT(testValue< T >("100", errorExpected, errorExpected, !errorExpected));
        CPPUNIT_ASSERT(testValue< T >("109", errorExpected, errorExpected, !errorExpected));
        CPPUNIT_ASSERT(testValue< T >("51", errorExpected, errorExpected, !errorExpected));

        CPPUNIT_ASSERT(testValue< T >("32767", errorExpected, errorExpected, !errorExpected));
    }

    // signed types specific tests
    // lexical_cast has a specific behavior for unsigned int with negative integers
    {
        // cast success for int16, int32, int64, float, [long] double
        T signedValue = 1;
        bool errorExpected = isBool || isInt8 || !isSigned;
        bool lcErrorExpected = isBool || isInt8; 
        //2**15-1
        typedef LimitLowest<std::int16_t, T> Limit16 ;
        CPPUNIT_ASSERT(testValue< T >("-32768", errorExpected, lcErrorExpected, !errorExpected, &signedValue));
        CPPUNIT_ASSERT( errorExpected || Limit16::check(signedValue) );

        // cast success for int32, int64, float, [long] double
        signedValue = 1;
        errorExpected = errorExpected || (sizeof(T) <= 2);
        lcErrorExpected = lcErrorExpected || (sizeof(T) <= 2);
        //2**31-1
        CPPUNIT_ASSERT(testValue< T >("-2147483648", errorExpected, lcErrorExpected, !errorExpected, &signedValue));
        typedef LimitLowest<std::int32_t, T> Limit32 ;
        CPPUNIT_ASSERT( errorExpected || Limit32::check(signedValue) );

        // cast success for int64, [long] double
        signedValue = 1;
        errorExpected = errorExpected || (sizeof(T) <= 4 && !isFloatingType);
        lcErrorExpected = lcErrorExpected || (sizeof(T) <= 4 && !isFloatingType);
        //2**63-1
        CPPUNIT_ASSERT(testValue< T >("-9223372036854775808", errorExpected, lcErrorExpected, !errorExpected, &signedValue));
        typedef LimitLowest<std::int64_t, T> Limit64 ;
        CPPUNIT_ASSERT( errorExpected || Limit64::check(signedValue) );

        // cast success for float, [long] double
        signedValue = 1;
        errorExpected = errorExpected || (sizeof(T) <= 8 && !isFloatingType);
        lcErrorExpected = lcErrorExpected || (sizeof(T) <= 8 && !isFloatingType);
        //2**64
        CPPUNIT_ASSERT(testValue< T >("-18446744073709551616", errorExpected, errorExpected, !errorExpected));
    }

    // intergers > 0 tests
    {
        // cast success for [u]int16, [u]int32, [u]int64, float, [long] double
        bool errorExpected = isBool || isInt8;
        CPPUNIT_ASSERT(testValue< T >("32767", errorExpected, errorExpected, !errorExpected)); //2**15-1

        // cast success for uint16, [u]int32, [u]int64, float, [long] double
        errorExpected = errorExpected || (sizeof(T) <= 2 && isSigned);
        CPPUNIT_ASSERT(testValue< T >("32768", errorExpected, errorExpected, !errorExpected));//2**15
        CPPUNIT_ASSERT(testValue< T >("65535", errorExpected, errorExpected, !errorExpected));//2**16-1

        // cast success for [u]int32, [u]int64, float, [long] double
        errorExpected = errorExpected || (sizeof(T) <= 2);
        CPPUNIT_ASSERT(testValue< T >("65536", errorExpected, errorExpected, !errorExpected));//2**16
        CPPUNIT_ASSERT(testValue< T >("2147483647", errorExpected, errorExpected, !errorExpected));//2**31-1

        // cast success for uint32, [u]int64, float, [long] double
        errorExpected = errorExpected || (sizeof(T) <= 4 && isSigned && !isFloatingType);
        CPPUNIT_ASSERT(testValue< T >("2147483648", errorExpected, errorExpected, !errorExpected));//2**31
        CPPUNIT_ASSERT(testValue< T >("4294967295", errorExpected, errorExpected, !errorExpected));//2**32-1

        // cast success for [u]int64, float, [long] double
        errorExpected = errorExpected || (sizeof(T) <= 4&& !isFloatingType);
        CPPUNIT_ASSERT(testValue< T >("4294967296", errorExpected, errorExpected, !errorExpected));//2**32
        CPPUNIT_ASSERT(testValue< T >("9223372036854775807", errorExpected, errorExpected, !errorExpected));//2**63-1

        // cast success for uint64, float, [long] double
        errorExpected = errorExpected || (sizeof(T) <= 8 && isSigned && !isFloatingType);
        CPPUNIT_ASSERT(testValue< T >("9223372036854775808", errorExpected, errorExpected, !errorExpected));//2**63
        CPPUNIT_ASSERT(testValue< T >("18446744073709551615", errorExpected, errorExpected, !errorExpected));//2**64-1

        // cast success for float, [long] double
        errorExpected = errorExpected || (sizeof(T) <= 8 && !isFloatingType);
        CPPUNIT_ASSERT(testValue< T >("18446744073709551616", errorExpected, errorExpected, !errorExpected));//2**64
    }

    // ascii chars shall pass with char and [un]signed char, fail with other types
    CPPUNIT_ASSERT(testValue< T >(".", !isInt8, !isInt8, isInt8));
    CPPUNIT_ASSERT(testValue< T >("-", !isInt8, !isInt8, isInt8));
    CPPUNIT_ASSERT(testValue< T >("+", !isInt8, !isInt8, isInt8));
    CPPUNIT_ASSERT(testValue< T >("A", !isInt8, !isInt8, isInt8));
    CPPUNIT_ASSERT(testValue< T >("z", !isInt8, !isInt8, isInt8));
    CPPUNIT_ASSERT(testValue< T >("_", !isInt8, !isInt8, isInt8));
    CPPUNIT_ASSERT(testValue< T >("*", !isInt8, !isInt8, isInt8));

    // floating value cast
    CPPUNIT_ASSERT(testValue< T >("-1.", !isFloatingType, !isFloatingType, isFloatingType));
    CPPUNIT_ASSERT(testValue< T >("1.0e10", !isFloatingType, !isFloatingType, isFloatingType));
    CPPUNIT_ASSERT(testValue< T >("-1.3e23", !isFloatingType, !isFloatingType, isFloatingType));
    CPPUNIT_ASSERT(testValue< T >("1.45", !isFloatingType, !isFloatingType, isFloatingType));
    CPPUNIT_ASSERT(testValue< T >("+1.45", !isFloatingType, !isFloatingType, isFloatingType));
    CPPUNIT_ASSERT(testValue< T >("0.", !isFloatingType, !isFloatingType, isFloatingType));
    CPPUNIT_ASSERT(testValue< T >("1.", !isFloatingType, !isFloatingType, isFloatingType));
    CPPUNIT_ASSERT(testValue< T >("-0.", !isFloatingType, !isFloatingType, isFloatingType));
    CPPUNIT_ASSERT(testValue< T >("+0.", !isFloatingType, !isFloatingType, isFloatingType));
    CPPUNIT_ASSERT(testValue< T >("0.264", !isFloatingType, !isFloatingType, isFloatingType));
    CPPUNIT_ASSERT(testValue< T >(".274", !isFloatingType, !isFloatingType, isFloatingType));
    CPPUNIT_ASSERT(testValue< T >("-.274", !isFloatingType, !isFloatingType, isFloatingType));
    CPPUNIT_ASSERT(testValue< T >("+.274", !isFloatingType, !isFloatingType, isFloatingType));
    CPPUNIT_ASSERT(testValue< T >("235620.264", !isFloatingType, !isFloatingType, isFloatingType));
    CPPUNIT_ASSERT(testValue< T >("234567890.9874651342", !isFloatingType, !isFloatingType, isFloatingType));
    CPPUNIT_ASSERT(testValue< T >("234567890987465134268468.2", !isFloatingType, !isFloatingType, isFloatingType));

    // big floating value cast
    {
        bool errorExpected = !isFloatingType;
        bool lcErrorExpected = !isFloatingType || (sizeof(T) < 8);
        bool sameResultExpected = !(errorExpected || lcErrorExpected) && isFloatingType;
        CPPUNIT_ASSERT(testValue< T >("1e300", errorExpected, lcErrorExpected, sameResultExpected));
    }

    // floating special values
    CPPUNIT_ASSERT(testValue< T >("-inf", !isFloatingType, !isFloatingType, isFloatingType));
    CPPUNIT_ASSERT(testValue< T >("+inf", !isFloatingType, !isFloatingType, isFloatingType));
    CPPUNIT_ASSERT(testValue< T >("inf", !isFloatingType, !isFloatingType, isFloatingType));
    CPPUNIT_ASSERT(testValue< T >("-infinity", !isFloatingType, !isFloatingType, isFloatingType));
    CPPUNIT_ASSERT(testValue< T >("+infinity", !isFloatingType, !isFloatingType, isFloatingType));
    CPPUNIT_ASSERT(testValue< T >("nan", !isFloatingType, !isFloatingType, isFloatingType));
    CPPUNIT_ASSERT(testValue< T >("NaN", !isFloatingType, !isFloatingType, isFloatingType));
    CPPUNIT_ASSERT(testValue< T >("Nan", !isFloatingType, !isFloatingType, isFloatingType));
    CPPUNIT_ASSERT(testValue< T >("NAN", !isFloatingType, !isFloatingType, isFloatingType));
    CPPUNIT_ASSERT(testValue< T >("nAN", !isFloatingType, !isFloatingType, isFloatingType));

    // these shall fail
    CPPUNIT_ASSERT(testValue< T >("1,", true, true, false));
    CPPUNIT_ASSERT(testValue< T >("234.567.2", true, true, false));
    CPPUNIT_ASSERT(testValue< T >("", true, true, false));
    CPPUNIT_ASSERT(testValue< T >("+zdaij1.45", true, true, false));
    CPPUNIT_ASSERT(testValue< T >("toto", true, true, false));
    CPPUNIT_ASSERT(testValue< T >("123 123", true, true, false));
    CPPUNIT_ASSERT(testValue< T >("1'23", true, true, false));
    CPPUNIT_ASSERT(testValue< T >("1\"23", true, true, false));
    CPPUNIT_ASSERT(testValue< T >("-1,45", true, true, false));
    CPPUNIT_ASSERT(testValue< T >("+1,45", true, true, false));
    CPPUNIT_ASSERT(testValue< T >("on", true, true, false));
    CPPUNIT_ASSERT(testValue< T >("off", true, true, false));
    CPPUNIT_ASSERT(testValue< T >("&\"'(-è_çà)", true, true, false));
}

//------------------------------------------------------------------------------

void LocaleTest::longDoubleTest()
{
    testType< long double >();
}

//------------------------------------------------------------------------------

void LocaleTest::doubleTest()
{
    testType< double >();

    double result = 0;

#if BOOST_VERSION >= 105700
    // This test fail with boost < 1.57
    // http://stackoverflow.com/questions/27791080/boost-spirit-parser-crashes-on-input
    ::fwLocale::valueCast< double >("1e310", result);
    CPPUNIT_ASSERT_EQUAL(std::numeric_limits<double>::infinity(), result);
#endif

    ::fwLocale::valueCast< double >("+inf", result);
    CPPUNIT_ASSERT_EQUAL(std::numeric_limits<double>::infinity(), result);

    result = 0;
    ::fwLocale::valueCast< double >("-inf", result);
    CPPUNIT_ASSERT_EQUAL(-std::numeric_limits<double>::infinity(), result);
}

//------------------------------------------------------------------------------

void LocaleTest::floatTest()
{
    testType< float >();

    float result = 0;
    ::fwLocale::valueCast< float >("1e300", result);
    CPPUNIT_ASSERT_EQUAL(std::numeric_limits<float>::infinity(), result);
    ::fwLocale::valueCast< float >("inf", result);
    CPPUNIT_ASSERT_EQUAL(std::numeric_limits<float>::infinity(), result);

    result = 0;
    ::fwLocale::valueCast< float >("-1e300", result);
    CPPUNIT_ASSERT_EQUAL(-std::numeric_limits<float>::infinity(), result);
    ::fwLocale::valueCast< float >("-inf", result);
    CPPUNIT_ASSERT_EQUAL(-std::numeric_limits<float>::infinity(), result);
}

//------------------------------------------------------------------------------

void LocaleTest::charTest()
{
    testType< char  >();
}

//------------------------------------------------------------------------------

void LocaleTest::uint8Test()
{
    testType< uint8_t  >();
}

//------------------------------------------------------------------------------

void LocaleTest::uint16Test()
{
    testType< uint16_t >();
}

//------------------------------------------------------------------------------

void LocaleTest::uint32Test()
{
    testType< uint32_t >();
}

//------------------------------------------------------------------------------

void LocaleTest::uint64Test()
{
    testType< uint64_t >();
}

//------------------------------------------------------------------------------

void LocaleTest::int8Test()
{
    testType< int8_t  >();
}

//------------------------------------------------------------------------------

void LocaleTest::int16Test()
{
    testType< int16_t >();
}

//------------------------------------------------------------------------------

void LocaleTest::int32Test()
{
    testType< int32_t >();
}

//------------------------------------------------------------------------------

void LocaleTest::int64Test()
{
    testType< int64_t >();
}

//------------------------------------------------------------------------------

void LocaleTest::boolTest()
{
    testType< bool >();

    CPPUNIT_ASSERT( !::fwLocale::valueCast< bool >( std::string("false") ));
    CPPUNIT_ASSERT( ::fwLocale::valueCast< bool >( std::string("true") ));
    CPPUNIT_ASSERT( !::fwLocale::valueCast< bool >("0"));
    CPPUNIT_ASSERT( ::fwLocale::valueCast< bool >("1"));

    CPPUNIT_ASSERT( !::fwLocale::valueCast< bool >("false"));
    CPPUNIT_ASSERT( ::fwLocale::valueCast< bool >("true"));

    // test exception
    bool exceptionThrown = false;
    try
    {
        ::fwLocale::valueCast< bool >("1664.42");
    }
    catch(::fwLocale::ValueCastException &)
    {
        exceptionThrown = true;
    }

    CPPUNIT_ASSERT(exceptionThrown);

    // additionnal fwLocale bool cast behavior
    bool result = false;
    CPPUNIT_ASSERT(testValue< bool >("true", false, true, false, &result));
    CPPUNIT_ASSERT(result);
    CPPUNIT_ASSERT(testValue< bool >("false", false, true, false, &result));
    CPPUNIT_ASSERT(!result);
}

//------------------------------------------------------------------------------

template<typename T>
void testGenerate(T value, std::string valueStr)
{
    std::string generated;
    const bool status = ::fwLocale::generate< T >(value, generated);

//"Failed to generate '" + valueStr + "' (generated = '" + generated + "')",

    CPPUNIT_ASSERT( status);

    CPPUNIT_ASSERT_EQUAL(valueStr, generated);
}

void LocaleTest::generateTest()
{
    testGenerate<int>(1664, "1664");

    testGenerate<double>(16.64, "16.64");
    testGenerate<double>(3.142138, "3.142138");
    testGenerate<float>(std::numeric_limits<double>::quiet_NaN(), "nan");
    testGenerate<float>(std::numeric_limits<double>::signaling_NaN(), "nan");
    testGenerate<double>(std::numeric_limits<double>::infinity(), "inf");
    testGenerate<double>(-std::numeric_limits<double>::infinity(), "-inf");

    testGenerate<float>(16.64f, "16.639999");
    testGenerate<float>(3.142f, "3.142");
    testGenerate<float>(3.141328f, "3.141328");
    testGenerate<float>(std::numeric_limits<float>::infinity(), "inf");
    testGenerate<float>(-std::numeric_limits<float>::infinity(), "-inf");
    testGenerate<float>(std::numeric_limits<float>::quiet_NaN(), "nan");
    testGenerate<float>(std::numeric_limits<float>::signaling_NaN(), "nan");

    testGenerate<bool>(true, "true");
    testGenerate<bool>(1, "true");
    testGenerate<bool>(false, "false");
    testGenerate<bool>(0, "false");
}

//------------------------------------------------------------------------------

} // namespace ut

*/

} // namespace fwLocale


int main()
{

    std::cout << "hu\n" ;
/*
    fwLocale::ut::LocaleTest t;
    t.int16Test();
    t.int32Test();
    t.int64Test();
*/
return 0;
}

