#include <utility>

template <class Function>
void higherOrderFunction(Function&& f) {
     std::forward<Function>(f)();
}

#include <iostream>
#include <memory>
int main()
{
    std::unique_ptr<int> p;
    auto l1 = [p = std::move(p)] {std::cout << __PRETTY_FUNCTION__ << '\n';};
    
    higherOrderFunction(l1);
    higherOrderFunction(std::move(l1));
    
    int i = 0;
    auto l2 = [=]() mutable { i = 0; std::cout << __PRETTY_FUNCTION__ << '\n'; };
    higherOrderFunction(l2);
    higherOrderFunction(std::move(l2));
}
