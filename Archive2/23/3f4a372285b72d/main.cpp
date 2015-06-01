#include <iostream>

namespace hide {
    struct s {};
    
    template< typename >
    void f() { std::cout << "working\n"; }

    void call( void (*fn) () ) {
        fn();
    }

}

int main() {
    call( hide::f< hide::s > );
}
