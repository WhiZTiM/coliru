#include <string>
#include <typeinfo>
#include <iostream>

template<class T1, class T2>
decltype(auto) add(const T1& t1, const T2& t2) { return t1 + t2; }

std::string add(const char * t1, const char* t2) { return std::string(t1) + t2; }

template<typename T1, typename T2>
auto sum(const T1& t1, const T2& t2) {
    return add(t1, t2);
}

template<typename T1, typename... T2>
auto sum(const T1& t1, const T2&... t2) {
    return add(t1, sum(t2...));
}



int main(int argc, char** argv) {
    auto s1 = sum(1, 2, 3);
    std::cout << typeid(s1).name() << " " << s1 << std::endl;

    auto s2 = sum(1, 2.0, 3);
    std::cout << typeid(s2).name() << " " << s2 << std::endl;

    auto s3 = sum("Hello", " ", std::string("World!"));
    std::cout << typeid(s3).name() << " " << s3 << std::endl;

    auto s4 = sum("Hello", " ", "World!");
    std::cout << typeid(s4).name() << " " << s4 << std::endl;

    return 0;
}