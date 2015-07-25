#include <iostream>
#include <string>
#include <type_traits>

#include <boost/variant.hpp>

template<class Result, class Func>
struct forwarding_visitor : Func, boost::static_visitor<Result>
{
    template<class T>
    forwarding_visitor(T && t): Func(std::forward<T>(t)) {}
};

template<class Result, class Func>
forwarding_visitor<Result, std::decay_t<Func> > make_forwarding_visitor(Func && func) {
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
   
   std::cout << boost::apply_visitor(visitor,p) << "\n";
   std::cout << boost::apply_visitor(visitor,d) << std::endl;
}