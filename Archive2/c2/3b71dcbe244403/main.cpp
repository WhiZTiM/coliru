#include <boost/functional/factory.hpp>
#include <boost/function.hpp>
#include <map>
#include <iostream>

struct A {};
struct AA : A {
    AA() { std::cout << __PRETTY_FUNCTION__ << "\n"; }
};
struct AB : A {
    AB() { std::cout << __PRETTY_FUNCTION__ << "\n"; }
};

typedef boost::function<A*()> creator;
typedef std::map<std::string, creator> factory;

struct C {
    C(factory &f){
        _f = f;
        for (auto& e : _f)
            std::cout << "entry for " << e.first << " present " << (!!e.second) << "\n";
    }
    factory _f;
};

int main() {
    factory f;
    f["1"] = boost::factory<AA*>();
    f["2"] = boost::factory<AB*>();

    C test(f);
    delete f["1"]();
    delete f["2"]();
    delete f["1"]();
    delete f["2"]();

    C test2(f);
    delete f["1"]();
    delete f["2"]();
    delete f["1"]();
    delete f["2"]();
}
