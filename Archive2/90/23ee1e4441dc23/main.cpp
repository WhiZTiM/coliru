#include <iostream>
#include <algorithm>
#include <vector>

template <
    template <class...> class Container,
    class Transform,
    class ContainerT,
    class... ContainerParams
>
auto map(Container<ContainerT, ContainerParams...> const &container, Transform &&transform) {
    using DestT = std::result_of_t<Transform(ContainerT const&)>;
    Container<DestT, ContainerParams...> res;
    
    using std::begin;
    using std::end;
    std::transform(
        begin(container),
        end(container),
        std::inserter(res, end(res)),
        std::forward<Transform>(transform)
    );
    
    return res;
}

int main() {
    std::vector<int> v1 {1, 2, 3, 4};
    auto v2 = map(v1, [](int i) -> float {
        return i * 1.5f;
    });
    
    for(float const &f : v2)
        std::cout << f << ' ';
    std::cout << '\n';
}