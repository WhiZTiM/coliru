#include <iostream>
#include <vector>
#include <type_traits>
#include <utility>
#include <cstddef>
#include <tuple>
#include <memory>

template <typename Result, typename... Parameters>
class Superposable
{
public:
    using result_t = Result;
    using params_t = std::tuple<Parameters...>;
    
    virtual void operator()(Result& result, const Parameters&...) const = 0;
};

class MyField : public Superposable<double, double, double>
{
public:
    void operator()(double& result, const double& p1, const double& p2) const
    {
        result = p1 + p2;
    }
};

template <typename, typename>
class Superposition_impl;

template <typename S, std::size_t... Is>
class Superposition_impl<S, std::index_sequence<Is...>>
{
    static_assert(std::is_base_of<Superposable<typename S::result_t, typename std::tuple_element<Is, typename S::params_t>::type...>, S>::value, "!");
    
public:
    std::vector<std::shared_ptr<S>> elements;

    void operator()(typename S::result_t& result, const typename std::tuple_element<Is, typename S::params_t>::type&... parameters) const
    {
        for (auto p : elements)
        {
            typename S::result_t r;
            (*p)(r, parameters...);
            result += r;
        }
    }
};

template <typename S>
using Superposition = Superposition_impl<S, std::make_index_sequence<std::tuple_size<typename S::params_t>::value>>;

int main()
{
    double d = 0.0;
    Superposition<MyField> s;    
    auto ptr = std::make_shared<MyField>();    
    s.elements.push_back(ptr);    
    s(d, 1.0, 2.0);
    std::cout << d;
}
