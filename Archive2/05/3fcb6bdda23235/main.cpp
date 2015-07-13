#include <iostream>
#include <string>
#include <boost/variant.hpp>


template<typename... R>
class foo
    : public R... {
public: 
};

class bar_1 {
public:
    void fn_1() { std::cout << "bar_1::fn_1()\n"; }
};

class bar_2 {
public:
    void fn_2() { std::cout << "bar_2::fn_2()\n"; }
};


using foo_inst = foo<bar_1, bar_2>;


int main() {
    foo_inst fi;
    fi.fn_1();
    fi.fn_2();
    
	return 0;
}
