#include <iostream>
#include <string>
#include <typeinfo>

#include <type_traits>

template < template <typename...> class Template, typename T >
struct is_instantiation_of : std::false_type {};

template < template <typename...> class Template, typename... Args >
struct is_instantiation_of< Template, Template<Args...> > : std::true_type {};

void add(const std::string &key, const std::string &val) {
    std::cout << "1st\n";
    std::cout << val << '\n';
}

template <class T = std::initializer_list<std::string>>
auto add(const std::string & key, T t)
-> std::enable_if_t<std::is_same<T, std::initializer_list<std::string>>{}>
{
    std::cout << "2nd\n";
    for(auto &&str : t)
        std::cout << str << '\n';
}

void add(const std::string & key, std::initializer_list<std::initializer_list<std::string>> t) {
    std::cout << "3rd\n";
    for(auto &&tt : t)
        for(auto &&str : tt)
            std::cout << str << '\n';
}

int main() {
    add("lol", "str");
    add("lol", {"str1", "str2", "str3", "str4"});
    add("lol", {{"str1", "str2"}, {"str3", "str4"}});
}