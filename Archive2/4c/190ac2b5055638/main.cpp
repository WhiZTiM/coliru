#include <iostream>
#include <string>
#include <utility>
#include <tuple>
#include <cstddef>
#include <type_traits>

template <std::size_t...> struct index_sequence {};
template <std::size_t N, std::size_t... Is> struct make_index_sequence : make_index_sequence<N-1, N-1, Is...> {};
template <std::size_t... Is> struct make_index_sequence<0, Is...> : index_sequence<Is...> {};

void dothing(bool testBool, const std::string& str, const std::string& file, int line, const std::string& defaultString = "")
{
    std::cout << testBool << " " << str << " " << file << " " << line << " " << defaultString << "\n";
}

template <typename... Args, std::size_t... Is>
void dothings2(bool testBool, index_sequence<Is...>, Args&&... args)
{
    auto tuple = std::make_tuple(std::forward<Args>(args)...);
    using expander = int[];
    static_cast<void>(expander{ 0, (dothing(testBool, std::get<Is>(tuple)
                               , std::get<sizeof...(Args)-2>(tuple)
                               , std::get<sizeof...(Args)-1>(tuple)), 0)... }); 
}

template <typename... Args, std::size_t... Is>
void dothings3(bool testBool, index_sequence<Is...>, Args&&... args)
{
    auto tuple = std::make_tuple(std::forward<Args>(args)...);
    using expander = int[];
    static_cast<void>(expander{ 0, (dothing(testBool, std::get<Is>(tuple)
                               , std::get<sizeof...(Args)-3>(tuple)
                               , std::get<sizeof...(Args)-2>(tuple)
                               , std::get<sizeof...(Args)-1>(tuple)), 0)... }); 
}

template <typename... Args>
auto dothings(bool testBool, Args&&... args)
    -> typename std::enable_if<std::is_convertible<typename std::tuple_element<sizeof...(Args)-1, std::tuple<Args...>>::type, std::string>{}>::type
{
    dothings3(testBool, make_index_sequence<sizeof...(Args)-3>{}, std::forward<Args>(args)...); 
}

template <typename... Args>
auto dothings(bool testBool, Args&&... args)
    -> typename std::enable_if<!std::is_convertible<typename std::tuple_element<sizeof...(Args)-1, std::tuple<Args...>>::type, std::string>{}>::type
{
    dothings2(testBool, make_index_sequence<sizeof...(Args)-2>{}, std::forward<Args>(args)...); 
}

int main()
{
    std::cout << "with string\n";
    dothings(true, "A", "B", "C", "D", "foo.cpp", 42, "bar");
    
    std::cout << "without string\n";
    dothings(true, "A", "B", "C", "D", "foo.cpp", 42);
}
