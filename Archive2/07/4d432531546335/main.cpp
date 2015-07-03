#include <iostream>
 
struct is_equal 
{
    template <typename T, typename U>
    struct apply {
       using type = typename std::is_same<T, U>::type;
    };
};
 
struct is_space 
{
    template <typename CharT>
    struct apply {
        using type = std::true_type;
    };
};

template <typename T, typename Stub = char>
struct takes_one {
    typedef char yes[1];
    typedef char no[2];
 
    template <typename C>
    static yes& test(typename C::template apply<Stub>*);
 
    template <typename>
    static no& test(...);
 
    static const bool value = sizeof(test<T>(nullptr)) == sizeof(yes);
};
 
int main () 
{
    std::cout << takes_one<is_space>::value << "\n";   // true
    std::cout << takes_one<is_equal>::value << "\n";   // false
}
