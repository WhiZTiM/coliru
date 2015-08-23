
#include <type_traits>


// First approach: conditional
template<int I> struct banana {
    float number;
    banana(float n) {
        number = n;
    }

    std::conditional_t<I == 0, float, int>
    getNumber() {
        return number;
    }
};

template<int /*I*/>
struct banana_return_type
{
    using type = int;
};

template<>
struct banana_return_type<0>
{
    using type = float;
};

// Second approach: template specialization
template<int I> struct bananaSecond {
    float number;
    bananaSecond(float n) {
        number = n;
    }

    typename banana_return_type<I>::type
        getNumber() {
        return number;
    }
};

int main(int argc, char** argv)
{
    // Conditional approach
    static_assert(std::is_same<decltype(std::declval<banana<0>>().getNumber()), float>::value, "Check");
    static_assert(std::is_same<decltype(std::declval<banana<1>>().getNumber()), int>::value, "Check");

    // Template specialization approach
    static_assert(std::is_same<decltype(std::declval<bananaSecond<0>>().getNumber()), float>::value, "Check");
    static_assert(std::is_same<decltype(std::declval<bananaSecond<1>>().getNumber()), int>::value, "Check");

    return 0;
}
