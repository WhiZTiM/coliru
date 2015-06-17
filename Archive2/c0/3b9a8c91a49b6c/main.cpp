#include <iostream>

namespace ajlb {
    
template<typename T>
struct metafunc {
    enum { Result = 1 };
};

}

namespace plop {
    struct s {};
}

namespace ajlb {
  template<>
    struct metafunc<plop::s> {
        enum { Result = 2 };
    };
}

int main() {
    std::cout << ajlb::metafunc<plop::s>::Result << std::endl;
}
