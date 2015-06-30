#include <iostream>

namespace ajlb {
    
template<typename T>
struct metafunc {
    enum { Result = 1 };
};

}

namespace plop {
    struct s {};
    
    template<>
    struct ajlb::metafunc<s> {
        enum { Result = 2 };
    };
}

int main() {
    std::cout << ajlb::metafunc<plop::s>::Result << std::endl;
}