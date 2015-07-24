#include <iostream>
#include <string>
#include <type_traits>

#include <boost/variant.hpp>

template<class Result, class Func>
struct forwarding_visitor : boost::static_visitor<Result>
{
    Func func;
    forwarding_visitor(Func& f):func(f){}
    forwarding_visitor(Func&& f):func(std::move(f)){}
    template<class Arg>
    Result operator()(Arg && arg) const {
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

struct Dir
{
    std::string name() const {return "foo"; }
};

int main()
{
   using variant = boost::variant<Person,Dir>;
   variant p = Person{};
   variant d = Dir{};
   auto visitor = make_forwarding_visitor<std::string>([](const auto& t){ return t.name();});
   
   std::cout << boost::apply_visitor(visitor,p) << std::endl;
   std::cout << boost::apply_visitor(visitor,d) << std::endl;
}