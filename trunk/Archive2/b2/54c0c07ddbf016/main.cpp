#include <type_traits>
#include <string>
#include <vector>
#include <set>
#include <iostream>

//struct ReserveWrapper
//{
    template<typename T, class R = decltype(std::declval<T>().reserve(T::size_type()))>
    inline static R try_reserve(T* t, typename T::size_type len)
    {
        std::cout << "ReserveWrapper reserve..." << std::endl;
        return t->reserve(len);
    };
    //template<typename T>
    inline static void try_reserve(...)
    {
        std::cout << "ReserveWrapper nothing..." << std::endl;
    };
//};

// 判断是否存在reserve方法
// http://blog.chinaunix.net/xmlrpc.php?r=blog/article&uid=17286628&id=4643663
template<typename T>
class ReserveWrapperT
{
    template<typename U, void (U::*)(typename U::size_type)> struct MethodMatcher;
    template<typename U> static std::true_type match(MethodMatcher<U, &U::reserve>*);
    template<typename U> static std::false_type match(...);
    const static bool value = decltype(match<T>(nullptr))::value;
    inline static void call(std::false_type, T&, typename T::size_type)
    {
        std::cout << "ReserveWrapperT nothing..." << std::endl;
    }
    inline static void call(std::true_type, T& t, typename T::size_type len)
    {
        std::cout << "ReserveWrapperT reserve..." << std::endl;
        t.reserve(len);
    }
public:
    inline static void try_reserve(T& t, typename T::size_type len)
    {
        call(decltype(match<T>(nullptr))(), t, len);
    }
};

int main()
{
    {
        std::vector<int> v;
        ReserveWrapperT<std::vector<int>>::try_reserve(v, 10);
        try_reserve(&v, size_t(20));
    }
    {
        std::set<int> v;
        ReserveWrapperT<std::set<int>>::try_reserve(v, 30);
        try_reserve(&v, size_t(40));
    }
    return 0;
}