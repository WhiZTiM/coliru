
#include <type_traits>



template<typename T>
struct A
{

    template<typename U, 
             typename std::enable_if<!std::is_floating_point<U>::value>::type = 0
            >
    void foo() {}

    template<typename U, 
             typename std::enable_if<std::is_floating_point<U>::value>::type = 0
            >
    void foo() {}
};

template<typename T>
struct B
{

    template<typename U, 
             typename = typename std::enable_if<!std::is_floating_point<U>::value>::type
            >
    void foo() {}

    template<typename U, 
             typename = typename std::enable_if<std::is_floating_point<U>::value>::type
            >
    void foo() {}
};

int main()
{
}
