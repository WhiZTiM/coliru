#include <boost/bind.hpp>
#include <boost/bind/protect.hpp>
#include <iostream>

struct A {
    template <typename H> void call_handler(H handler) { 
        handler(); 
    }
};

struct B {
    struct handler_caller_f {
        typedef void result_type;

        template <typename H> void operator()(B* this_, H handler) const {
            handler();
        }
    };

    template <typename H> void run(H handler) {
        m_a.call_handler(boost::bind(handler_caller_f(), this, boost::protect(handler)));
    }

    A m_a;
};

struct Test {
    void handler() { std::cout << __PRETTY_FUNCTION__ << "\n"; }
};

int main() {
    Test t;

    B b;
    b.run(boost::bind(&Test::handler, &t));
}
