#include <iostream>
#include <string>
#include <type_traits>


template<class Result, class Func>
struct forwarding_visitor // : boost::static_visitor<Result>
{
    typedef Result result_type; // In real case will be inherited from boost::static_visitor<Result>
    Func func;
    
    template<class Arg>
    result_type operator()(Arg && arg) const {
        return func(std::forward<Arg>(arg));
    }
};

template<class Result, class Func>
forwarding_visitor<Result, typename std::decay<Func>::type> make_forwarding_visitor(Func && func) {
    return {std::forward<Func>(func)};
}

struct Person
{
   std::string name() const { return "Jens"; }
};

int main()
{
   Person p;
   
   auto visitor = make_forwarding_visitor<std::string>([](const auto& t){ return t.name();});
   
   std::cout << visitor(p) << std::endl;
}