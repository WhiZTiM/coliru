#include <iostream>
#include <tuple>
#include <functional>

namespace detail
{
template<typename T>
struct tuple_with_placeholder : T
{
    using T::T;

    template<typename PH>
    auto operator[](PH) const
    {
        return std::get<std::is_placeholder<PH>::value-1>(*this);
    }
};
}

#define LR(EXPR) (auto&&... ps) { \
    detail::tuple_with_placeholder<decltype(std::forward_as_tuple(ps...))> p(ps...); \
    using namespace std::placeholders; \
    return EXPR; \
}

int main()
{
    std::cout << []LR(p[_1])("test");
    std::cout << []LR(p[_1]+p[_2])(2, 3); 
    std::cout << []LR(p[_1]+p[_2])(std::string("hello "), std::string(" world!"));
}
