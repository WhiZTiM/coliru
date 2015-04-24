//http://stackoverflow.com/questions/23230003/something-between-func-and-pretty-function/29856690?noredirect=1#comment47839355_29856690
#include <cstring>
#include <string>
#include <algorithm>

template<size_t FL, size_t PFL>
const char* computeMethodName(const char (&function)[FL], const char (&prettyFunction)[PFL]) {
    using reverse_ptr = std::reverse_iterator<const char*>;
    thread_local static char result[PFL];
    const char* locFuncName = std::search(prettyFunction,prettyFunction+PFL-1,function,function+FL-1);
    const char* locClassName = std::find(reverse_ptr(locFuncName), reverse_ptr(prettyFunction), ' ').base();
    const char* endFuncName = std::find(locFuncName,prettyFunction+PFL-1,'(');
    std::copy(locClassName, endFuncName, result);
    return result;
}
#define __COMPACT_PRETTY_FUNCTION__ computeMethodName(__FUNCTION__,__PRETTY_FUNCTION__)

#include <iostream>
typedef int(*f)(int);
struct A {
    A(f p) {
        std::cout << __COMPACT_PRETTY_FUNCTION__ << '\n';
    }
    A(const A& rhs)
    {
        std::cout << __COMPACT_PRETTY_FUNCTION__ << '\n';
    }
    f B(f p) {
        std::cout << __COMPACT_PRETTY_FUNCTION__ << '\n';
        return p;
    }
    static f C(f p) {
        std::cout << __COMPACT_PRETTY_FUNCTION__ << '\n';
        return p;
    }
    A& operator=(const A& rhs)
    {
        std::cout << __COMPACT_PRETTY_FUNCTION__ << '\n';
        return *this;
    }
};
f D(f p) {
    std::cout << __COMPACT_PRETTY_FUNCTION__ << '\n';
    return p;
}

int main() {
    A a(0);
    a.B(0);
    a.C(0);
    D(0);
    A a2=a;
    a2 = a;
    return 0;
}