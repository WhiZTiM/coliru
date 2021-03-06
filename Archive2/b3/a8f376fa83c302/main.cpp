#include <iostream>
#include <type_traits>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/string.hpp>
#include <boost/mpl/at.hpp>

struct JInt {};
struct JBool {};
struct JVoid {};

template <typename _IndexedType>
struct JArray {
    static const bool HasIndexedType = true;
    using IndexedType = _IndexedType;
};

typedef boost::mpl::vector<JInt, JBool, JVoid> non_array_types;

typedef boost::mpl::map<
        boost::mpl::pair<JInt, boost::mpl::string<'I'>>,
        boost::mpl::pair<JBool, boost::mpl::string<'Z'>>,
        boost::mpl::pair<JVoid, boost::mpl::string<'V'>>
    > basic_type_sigmap;

template <typename T>
constexpr 
typename std::enable_if<boost::mpl::contains<non_array_types, T>::value, std::string>::type
Signature()
{
    typedef typename boost::mpl::at<basic_type_sigmap, T>::type sigStr;
    return boost::mpl::c_str<sigStr>::value;
}

template <typename T>
constexpr
typename std::enable_if<!boost::mpl::contains<non_array_types, T>::value, std::string>::type
Signature()
{
    return "[" + Signature<typename T::IndexedType>();
}

template <typename Arg>
constexpr std::string MakeSig()
{
    return Signature<Arg>();
}

template <typename Arg1, typename Arg2, typename ...Args>
constexpr std::string MakeSig()
{
    return Signature<Arg1>() + MakeSig<Arg2, Args...>();
}

template <typename RetType, typename ...ArgTypes>
constexpr std::string MakeFunctionSignature()
{
    return "(" + MakeSig<ArgTypes...>() + ")" + Signature<RetType>();
}

int main() 
{
    std::cout << Signature<JVoid>() << std::endl;
    std::cout << Signature<JArray<JArray<JVoid>>>() << std::endl;
    std::cout << MakeFunctionSignature<JVoid, JInt, JArray<JArray<JBool>>>() << std::endl;
}