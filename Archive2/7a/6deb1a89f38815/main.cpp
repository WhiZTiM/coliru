#include <iostream>
#include <string>


#include <boost/variant.hpp>

using namespace std;

struct Person
{
   string name() const { return "Jens"; }
};

struct Dir
{
    string name() const {return "foo"; }
};

template<class R,class callable>
struct generic_member_visitor : boost::static_visitor<R>
{
    const callable& c;
    generic_member_visitor(const callable& c):c(c){}
    template<class T>
    std::string operator()(const T& t)const
    {
        return c(t);
    }
};

template<typename R, typename F>
generic_member_visitor<R, typename std::decay<F>::type> make_visitor(F&& f)
{
    return { std::forward<F>(f) };   
}

int main()
{
   using variant = boost::variant<Person,Dir>;
   variant p = Person{};
   variant d = Dir{};
   auto gmc = make_visitor<std::string>([](const auto& t){ return t.name(); });
   
   cout << boost::apply_visitor(gmc,p) << endl;
   cout << boost::apply_visitor(gmc,d) << endl;
}