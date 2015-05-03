#include <iostream>
#include <vector>

namespace details {
    struct adl_helper { };
    
    template <class T, class Adl>
    std::vector<T> make_vector(Adl, size_t size) {
        return std::vector<T>(size);
    }
    
    template <class T, class Adl, class... Args, class R=std::vector<decltype(make_vector<T>(Adl{}, std::declval<Args>()...))>>
    R make_vector(Adl, size_t first, Args... sizes) 
    {
        auto inner = make_vector<T>(Adl{}, std::forward<Args>(sizes)...);
        return R(first, inner);
    }
}


template <class T, class... Args, class R=decltype(details::make_vector<T>(details::adl_helper{}, std::declval<Args>()...))>
R make_vector(Args... args)
{
    return details::make_vector<T>(details::adl_helper{}, std::forward<Args>(args)...);
}

int main()
{
    std::size_t n = 5;
    auto x = make_vector<int>(n + 1, n * 2, n * 3, n * 4);
    static_assert(std::is_same<decltype(x), std::vector<std::vector<std::vector<std::vector<int>>>>>::value, "");
}