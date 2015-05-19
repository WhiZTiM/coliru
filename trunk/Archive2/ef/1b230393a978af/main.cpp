#include<boost/phoenix.hpp>
#include<iostream>

namespace mylib{

    template<class T>
    struct myclass{};

    template<class P, class T>
    auto operator<<(
        myclass<P>& p,
        boost::phoenix::actor<
            boost::proto::exprns_::basic_expr<
                boost::proto::tagns_::tag::terminal, 
                boost::proto::argsns_::term<T>, 
                0l
            > 
        > t
    )->decltype(p){
        std::cout << __PRETTY_FUNCTION__ << " arg: " << t() << "\n";
        return p; //  << "expression[" << t() << "]";
    }
}

int main(){
    mylib::myclass<int> A;
    A << boost::phoenix::val(3.);
}
