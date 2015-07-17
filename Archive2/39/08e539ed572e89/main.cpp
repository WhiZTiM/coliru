#include <iostream>
#include <vector>
#include <string>
#include <cstddef>
#include <utility>
#include <tuple>
#include <iterator>

bool all(bool a)
{
    return a;
}

template <typename... B>
bool all(bool a, B... b)
{
    return a && all(b...);
}

template <typename OutputIterator, typename NaryOperator, typename... InputIterators, std::size_t... Is>
OutputIterator transform(OutputIterator result, NaryOperator op, std::index_sequence<Is...>, InputIterators... iterators)
{
    auto tuple = std::make_tuple(iterators...);
    while (all(std::get<2*Is>(tuple) != std::get<2*Is + 1>(tuple)...))
    {
        *result = op((std::get<2*Is>(tuple) != std::get<2*Is + 1>(tuple) ? *std::get<2*Is>(tuple)++ : typename std::iterator_traits<typename std::tuple_element<2*Is, decltype(tuple)>::type>::value_type{})...);
        ++result;
    }
    return result;
}

template <typename OutputIterator, typename NaryOperator, typename... InputIterators>
OutputIterator transform(OutputIterator result, NaryOperator op, InputIterators... iterators)
{
    return transform(result, op, std::make_index_sequence<sizeof...(InputIterators)/2>{}, iterators...);
}

int main()
{
    const std::vector<int> a = {1,2,3,4,5};
    const std::vector<double> b = {1.2, 4.5, 0.6, 2.8, 3.1};
    const std::vector<std::string> c = {"hi", "howdy", "hello", "bye", "farewell"};
    std::vector<double> result(5);
    
    transform (result.begin(),
        [] (int i, double d, const std::string& s) -> double
        {
            return i + d + s.length();
        },
        a.begin(), a.end(),
        b.begin(), b.end(),
        c.begin(), c.end());
        
    for (double x : result) std::cout << x << ' ';  // 4.2 11.5 8.6 9.8 16.1
}
