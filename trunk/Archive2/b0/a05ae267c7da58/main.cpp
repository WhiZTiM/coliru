#include <iostream>
#include <string>
#include <map>
#include <sstream>

using namespace std;

namespace static_if_detail {

struct identity {
    template<typename T>
    T operator()(T&& x) const {
        return std::forward<T>(x);
    }
};

template<bool Cond>
struct statement {
    template<typename F>
    void then(const F& f){
        f(identity());
    }

    template<typename F>
    void else_(const F&){}
};

template<>
struct statement<false> {
    template<typename F>
    void then(const F&){}

    template<typename F>
    void else_(const F& f){
        f(identity());
    }
};

} //end of namespace static_if_detail

template<bool Cond, typename F>
static_if_detail::statement<Cond> static_if(F const& f){
    static_if_detail::statement<Cond> if_;
    if_.then(f);
    return if_;
}

template<typename T>
void decrement_kindof(T& value){
    static_if<std::is_same<std::string, T>::value>([&](auto){
        value.pop_back();
    }).else_([&](auto){
        --value;
    });
}

int main()
{
    string s{"fuffas"};
    decrement_kindof(s);
    cout << s << endl;
}
