#include <sstream>
#include <iostream>
#include <string>
#include <utility>
#include <functional>
#include <vector>

#define ADL

template<class T>
struct toy {
    T t = {};
    toy& operator*=(T const& o){
        t*=o;
        return *this;
    }
#ifdef ADL
    friend toy operator*(toy t, T s){
        t*=s;
        return t;
    }
    friend toy operator*(T s, toy t){
        t*=s;
        return t;
    }
#endif
};
#ifndef ADL
template<class T>
    toy<T> operator*(toy<T> t, T s){
        t*=s;
        return t;
    }
template<class T>
    toy<T> operator*(T s, toy<T> t){
        t*=s;
        return t;
    }
#endif

struct bob {
    int state;
    operator int&(){return state;}
};

int main() {
    bob b;
    toy<int> x;
    b * x;
}
