#include <string>

std::string computeMethodName(const std::string& function, const std::string& prettyFunction);

#define __COMPACT_PRETTY_FUNCTION__ computeMethodName(__FUNCTION__,__PRETTY_FUNCTION__).c_str() //c_str() is optional


std::string computeMethodName(const std::string& function, const std::string& prettyFunction) {
    size_t locFunName = prettyFunction.find(function); //If the input is a constructor, it gets the beginning of the class name, not of the method. That's why later on we have to search for the first parenthesys
    size_t begin = prettyFunction.rfind(" ",locFunName) + 1;
    size_t end = prettyFunction.find("(",locFunName + function.length()); //Adding function.length() make this faster and also allows to handle operator parenthesys!
    if (prettyFunction[end + 1] == ')')
        return (prettyFunction.substr(begin,end - begin) + "()");
    else
        return (prettyFunction.substr(begin,end - begin) + "(...)");
}

#include <iostream>
struct A {
    typedef long long(*f)(long long);
    static f B(f) {
        std::cout << __PRETTY_FUNCTION__ << '\n';
        std::cout << __COMPACT_PRETTY_FUNCTION__;
        return '\0';
    }
};

int main() {
    A::B(0);
}