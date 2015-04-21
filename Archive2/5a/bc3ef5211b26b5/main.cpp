#include <utility>
#include <type_traits>


int foo()
{
    return 0;
}


int main()
{   
    using result_type = typename std::result_of<decltype(foo)>::type;
}
