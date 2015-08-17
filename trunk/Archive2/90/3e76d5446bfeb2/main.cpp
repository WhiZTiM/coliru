#include <iostream>
#include <tuple>

#include <utility>

template <class F1, class F2>
decltype(auto) operator >> (F1 &&f1, F2 &&f2){
    using namespace std;
    return f2(forward<F1>(f1));
}

template <class F1, class F2>
decltype(auto) operator << (F1 &&f1, F2 &&f2){
    using namespace std;
    return f1(forward<F2>(f2));
}


// curry 2 args pack (temporary)
#define f(...) \
    [](auto&& ...args1){return  \
        [&](auto&& ...args2){return __VA_ARGS__ (std::forward<decltype(args1)>(args1)..., args2...);} ;   /* <-- ICE HERE!*/  \
    }


using namespace std;


auto sum(int a, int b){
    return a+b;
}

auto divide(int a, int b){
    return a/b;
}


int main() {
    float a = 10;
    float b = 20;

    auto part1 =  f(divide) << 5;

    auto res = sum(a,b) >> f(divide) << 5;

    auto res_ctrl = divide(sum(a,b), 5.0);


    cout << "res : "<< res << endl;
    cout << "ctrl: "<< res_ctrl << endl;

    return 0;
}