#include <iostream>

template<typename ... Ts>
struct System : public System<Ts> ...
{
    template<typename T>
    T& get()
    {
        static_assert(std::is_base_of<System<T>, System<Ts...>>::value, "the requested type does not exist in this system");
        return System<T>::value;
    }
};

template<typename T>
struct System<T>
{
    T value{};
};

int main()
{
    System<int, std::string, char> test;
 
    test.get<std::string>() = "Hello world ! ";
    std::cout << test.get<uint32_t>() << std::endl << test.get<int>() << std::endl;
 
    return 0;
}