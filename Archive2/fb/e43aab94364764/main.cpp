#include <iostream>
#include <vector>
#include <memory>

template<class PtrContainerT, typename = decltype( std::declval<PtrContainerT>()->back())> //probably pretty much constrains the intended use
inline void f2(PtrContainerT&& p) {
    using T = typename PtrContainerT::element_type::value_type; //in case you need to know T
    std::cout << "bla" << std::endl;
}

int main() {
    f2(std::make_shared<std::vector<int>>());
}
