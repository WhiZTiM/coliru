#include <type_traits>
#include <iostream>


template<typename Archive, typename T>
void serialize(Archive& ar, T t)
{
    if (std::is_enum<T>::value)
    {
        ar << static_cast<typename std::underlying_type<T>::type>(t);
    }
    else
    {
        ar << t;
    }
}


int main()
{
    serialize(std::cout, 3);
}
