#include <iostream>
#include <string>
#include <boost/variant/static_visitor.hpp>
using namespace std;

struct Person
{
   string name() const { return "Jens"; }
};

template< class K >
struct generic_member_visitor : boost::static_visitor<K>
{
    template<class T, class callable>
    K operator()(callable&& c, T&& t) const
    {
        return c(forward<T>(t));
    }
};

template< class K, class U >
struct MemberCaller
{
    U call;
    MemberCaller( U u ) : call(move(u)) {}
    
    auto operator()( K&& k ) const -> decltype( (k.*call)() )
    {
        return (k.*call)();
    }
};

template< class K, class U >
MemberCaller<K,U> make_defered_call( K&&, U u )
{
    return MemberCaller<K,U>{ u };
}

int main()
{
   Person p;
   auto lambda = make_defered_call(p, &Person::name);
   generic_member_visitor<std::string> v;
   cout << v(lambda, p) << endl;
}
