#include <iostream>
#include <fstream>
#include <type_traits>
#include <utility>
#include <string>

#define LOUD() std::cout << __PRETTY_FUNCTION__ << std::endl

struct Thing {
    int a, b;
    void load (std::istream& is) { LOUD(); is >> std::skipws >> a >> b;}
};

struct Object {
    int a, b, c;
    void load (std::istream& is) { LOUD(); is >> std::skipws >> a >> b >> c;}
};


namespace details {    
    template<class T>
    auto has_load_impl(int) 
         -> decltype((void)std::declval<T&>().load(std::declval<std::istream&>()),
                     std::true_type());

    template<class T>
    std::false_type has_load_impl(...);

    template<class T>
    using has_load = decltype(has_load_impl<T>(0));
    
    template<class T>
    void do_load(std::istream& is, T& t, std::true_type /*has_load*/){
        LOUD();
        t.load(is);
    }

    template<class T>
    void do_load(std::istream& is, T& t, std::false_type /*has_load*/){
        LOUD();
        is >> t;
    }
}

template<class T>
void load(std::istream& is, T& t){
    LOUD();
    details::do_load(is, t, details::has_load<T>());
}

void load(std::istream& is, std::string& s){
    LOUD();
    while (std::getline (is, s) && s.empty());
}

template<class... Args>
void PassArgs(std::istream& is, Args&... args){
    using expander = int[];
    (void)expander{0, (load(is, args), void(), 0)... };
}

template <typename T, typename... Args>
T* create (std::istream& is, Args&... args) {
    PassArgs(is, args...);
    T* t = new T(args...);
    // Do whatever with t;
    return t;
}

struct Meow {
    Meow(Thing, Object, int, double, std::string) {}
};

int main() {
    Thing t;
    Object o;
    int i;
    double d;
    std::string s;
    create<Meow>(std::cin, t, o, i ,d, s);
}