#include<type_traits>
#include<vector>
#include<iostream>


template<typename ...> using void_t = void;

template< typename, typename = void>
struct has_bracket_operator : public std::false_type {};

template<typename V>
struct has_bracket_operator<V, void_t<decltype(std::declval<const V>()[int{}])> >
     : public std::true_type{};

template<typename, typename = void>
struct has_parenthesis_operator : public std::false_type {};

template<typename V>
struct has_parenthesis_operator<V, void_t<decltype(std::declval<const V>()(int{}))> >
     : public std::true_type{};


int main()
{
    std::cout<<has_bracket_operator<std::vector<int> >::value<<std::endl;
    std::cout<<has_parenthesis_operator<std::vector<int> >::value<<std::endl;
}