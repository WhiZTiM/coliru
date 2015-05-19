#include<boost/phoenix.hpp>
#include<iostream>

namespace mylib{

    template<class T>
    struct myclass{};

    template<class P, class Actor>
    auto operator<<(myclass<P>& p, Actor&& t) -> decltype(p) {
        std::cout << __PRETTY_FUNCTION__ << " arg: " << t() << "\n";
        return p;
    }
}

int main(){
    mylib::myclass<int> A;
    A << boost::phoenix::val(3.);
}
