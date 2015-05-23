#include <utility>
#include <type_traits>
#include <boost/signals2/signal.hpp>

template<class T>
struct passkey
{
private:
    passkey() = default;
    passkey(passkey const&) = delete;
    
    friend T;
};

namespace detail
{
template<class> struct type{};

template<class... Ts>
struct types : type<Ts>...{};

template<class T, class... Ts>
struct one_of : std::is_base_of<type<T>, types<Ts...>> {};

} // detail::

template<class... Ts>
struct allow
{
    template<class T>
    allow(passkey<T> const&)
    {
        static_assert(detail::one_of<T, Ts...>(), "Type not allowed for this function.");
    }
};

namespace bs = boost::signals2;

template<class Signature, class Owner>
class private_signal
    : private bs::signal<Signature>
{
    friend Owner;
    
    using bs::signal<Signature>::signal;
    
public:
    using bs::signal<Signature>::connect;
};

template<class Signature, class Owner, class... VIPs>
class locked_signal
    : private bs::signal<Signature>
{
    friend Owner;
    
    using base = bs::signal<Signature>;
    
    using base::signal;
    
public:
    using bs::signal<Signature>::connect;
    
    template<class... Args>
    typename base::result_type operator()(allow<Owner, VIPs...>, Args&&... args)
    {
        return base::operator()(std::forward<Args>(args)...);
    }
    
    template<class... Args>
    typename base::result_type operator()(allow<Owner, VIPs...>, Args&&... args) const
    {
        return base::operator()(std::forward<Args>(args)...);
    }
};

struct X;

struct foo
{
    private_signal<void(), foo> on_stuff;
    
    locked_signal<void(), foo, X> on_blub;
    
    void test() { on_stuff(); }
};

struct X
{
    void call_blub(foo& f) { f.on_blub(passkey<X>{}); }
};

#include <iostream>

int main()
{
    foo f;
    f.on_stuff.connect([]{ std::cout << "whoo\n"; });
    f.on_blub.connect([]{ std::cout << "whoo2\n"; });
    
    f.test();
    f.on_blub(passkey<X>{});
    
    X x;
    x.call_blub(f);
}