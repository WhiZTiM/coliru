#include <iostream>
#include <string>
#include <utility>
#include <tuple>

void dothing(bool testBool, const std::string& str, const std::string& file, int line, const std::string& defaultString)
{
    std::cout << testBool << " " << str << " " << file << " " << line << " " << defaultString << "\n";
}

template <typename... Args, std::size_t... Is>
void dothings(bool testBool, std::index_sequence<Is...>, Args&&... args)
{
    auto tuple = std::make_tuple(std::forward<Args>(args)...);
    using expander = int[];
    static_cast<void>(expander{ (dothing(testBool, std::get<Is>(tuple)
                               , std::get<sizeof...(Args)-3>(tuple)
                               , std::get<sizeof...(Args)-2>(tuple)
                               , std::get<sizeof...(Args)-1>(tuple)), 0)... }); 
}

template <typename... Args>
void dothings(bool testBool, Args&&... args)
{
    dothings(testBool, std::make_index_sequence<sizeof...(Args)-3>{}, std::forward<Args>(args)...); 
}

int main()
{
    dothings(true, "A", "B", "C", "D", "foo.cpp", 42, "bar");
}
