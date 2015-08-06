#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
#include <set>

template <typename T>
struct function_traits
    : public function_traits<decltype(&T::operator())>
{};
// For generic types, directly use the result of the signature of its 'operator()'

template <typename ClassType, typename ReturnType, typename... Args>
struct function_traits<ReturnType(ClassType::*)(Args...) const>
// we specialize for pointers to member function
{
    enum { arity = sizeof...(Args) };
    // arity is the number of arguments.

    typedef ReturnType result_type;

    template <size_t i>
    struct arg
    {
        typedef typename std::tuple_element<i, std::tuple<Args...>>::type type;
        // the i-th argument is equivalent to the i-th tuple element of a tuple
        // composed of those arguments.
    };
};

template< class Collection, typename Transformation, class ResultCollection = std::vector< typename function_traits<Transformation>::result_type > >
ResultCollection Transform(const Collection& c, Transformation t)
{
    ResultCollection result(c.size());
    transform(c.begin(), c.end(), result.begin(), t);
    return result;
}

int main()
{
    std::vector<int> foo1 = {1,2,3,4,5};
    auto result1 = Transform( foo1, [] (const int & element) { return element + 5; });
    for (auto e : result1)
        std::cout << e << "\t";
    std::cout << std::endl;
    std::set<int> foo2 = {1,2,3,4,5};
    auto result2 = Transform( foo2, [] (const int & element) { return element + 30; });
    for (auto e : result2)
        std::cout << e << "\t";
    return 0;
}