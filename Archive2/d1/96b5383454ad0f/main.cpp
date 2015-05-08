#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

struct noop{
    template <class F> noop else_(const F & f) const { return noop {}; }
    template <class F> noop else_if(const F & f) const { return noop {}; }
    template <class F> noop operator()(const F & f) const { return noop {}; }
};

struct yes{
    template <class F> noop operator()(const F & f) const { f(0); return noop {}; }
    template <class F> noop else_if(const F & f) const { return noop {}; }
};

struct no{
    template <class F> auto else_(const F & f) const { f(0); }
    yes else_if(std::true_type) { return yes {}; }
    no  else_if(std::false_type) { return no {}; }
    template <class F> no operator()(const F & f) const { return no {}; }
};

yes static_if(std::true_type) { return yes {}; }
no  static_if(std::false_type) { return no {}; }

template <typename T>
void foo(T & t)
{
    using U = std::decay_t<decltype(t)>;
    t = U();
    static_if(std::is_same<U, int>())([&](auto) { t += 2; })
    .else_if(std::is_same<U, std::string>())([&](auto) { t += "OK"; })
    .else_if(std::is_same<U, std::vector<double>>())([&](auto) { t.push_back(210.45); })
    .else_([&](auto){})
    ;
}


int main()
{
    int n {5};
    std::string s {"test"};
    std::vector<double> a {1.6, 2.15, 3};
    bool flag = true;
    
    foo(n);
    foo(s);
    foo(a);
    foo(flag);
    
    std::cout << n << s << a[0] << flag;
}
