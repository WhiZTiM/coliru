#include <iostream>
#include <typeinfo>
#include <string>
#include <cxxabi.h>

using namespace std;

string demangle(const char* mangledName) {
    int status;
    char* result = abi::__cxa_demangle(mangledName, nullptr, nullptr, &status);
    switch(status) {
    case -1:
        cerr << "Out of memory!" << endl;
        exit(1);
    case -2:
        return mangledName;
    case -3: // Should never happen, but just in case?
        return mangledName;
    }
    string name = result;
    free(result);
    return name;
}

template<typename T> struct preserve_qualifiers {};

template<typename T> class typeinfo {
    using wrap = preserve_qualifiers<T>;
public:
    static const string name() {
        string name = demangle(typeid(wrap).name());
        int i = name.find_first_of('<');
        if(i == string::npos) return name;
        int j = name.length() - i - 2;
        return name.substr(i + 1, j);
    }
};

#define TypeOut(...) cout \
    << "Type " #__VA_ARGS__ ": " << endl \
    << "  Mangled: " << typeid(__VA_ARGS__).name() << endl \
    << "  Demangled: " << demangle(typeid(__VA_ARGS__).name()) << endl \
    << "  typeinfo<>: " << typeinfo<__VA_ARGS__>::name() << endl
class A {};
template<typename T> class F {};
template<int T> class G {};
template<template<typename> class T> class H {};
template<template<int> class T> class I {};
template<typename... T> class J {};
template<int... T> class K {};
template<template<typename> class... T> class L {};
template<template<int> class... T> class M {};
template<template<typename> class... T> class N {};
template<template<template<typename> class...> class... T> class O {};
struct bits {int i : 4, j : 2;};
template<typename T, int n> struct bits2 {T val : n;};

namespace cheese
{
    class blue {};
    class green : public blue {};
}

int main(int argc, char* argv[]) {
//    TypeOut(void(*volatile)(void(*const)()));
//    TypeOut(int (A::*)());
//    TypeOut(int (A::*)()const);
//    TypeOut(int (A::*const)());
//#ifdef __clang__
//    TypeOut(int (A::*)()&);
//    TypeOut(int (A::*)()&&);
//#endif
//    TypeOut(F<int>);
//    TypeOut(G<3>);
//    TypeOut(H<F>);
//    TypeOut(I<G>);
//    TypeOut(J<int>);
//    TypeOut(K<3>);
//    TypeOut(L<F>);
//    TypeOut(M<G>);
//    TypeOut(N<F,F,F>);
//    TypeOut(O<N,N>);
    TypeOut(cheese::green);
}