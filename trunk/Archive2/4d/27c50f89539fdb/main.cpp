#include <utility>

template<typename T, template<typename, typename...> typename Ptr, typename U>
Ptr<T> smart_ptr_cast(Ptr<U>&& ptr) {
    return Ptr<T>(std::forward<Ptr<U>>(ptr));
}

// example:
#include <iostream>
#include <memory>
#include <typeinfo>

class B { };
class D : public B { };

int main() {
    auto a = smart_ptr_cast<B>(std::make_unique<D>());
    auto b = smart_ptr_cast<B>(std::make_shared<D>());
    std::cout << typeid(a).name() << '\n';
    std::cout << typeid(b).name() << '\n';
    return 0;
}