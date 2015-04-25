#include <type_traits>
#include <typeinfo>
#include <iostream>

template<typename F>
using eval_metafunction = typename F::type;

//Example
using common = eval_metafunction<std::common_type<int,char>>;

int main()
{
    std::cout << typeid(common).name() << std::endl; 
}
