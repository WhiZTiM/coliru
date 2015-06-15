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


    template<int I> struct rank : rank<I-1> { static_assert(I > 0, ""); };
    template<> struct rank<0> {};


template<typename VectorType>
struct VectorWrapper
{
    auto get(int i) const
    {
        return get(i, has_bracket_operator<VectorType>(), has_parenthesis_operator<VectorType>());
    }
    
    auto get(int i, std::true_type /*brackets*/, std::false_type /*parenthesis*/) const
    {
        return v[i];
    }

    auto get(int i, std::false_type /*brackets*/, std::true_type /*parenthesis*/) const
    {
        return v(i);
    }

    VectorType v;
};

int main()
{
    std::cout<<has_bracket_operator<std::vector<int> >::value<<std::endl;
    std::cout<<has_parenthesis_operator<std::vector<int> >::value<<std::endl;
    
    VectorWrapper<std::vector<int> > v;
    v.v.push_back(1);
    std::cout << v.get(0) << std::endl;
}