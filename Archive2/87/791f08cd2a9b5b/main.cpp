#include <iostream>
#include <type_traits>

int main()
{
    std::cout << std::boolalpha << std::is_pointer<std::nullptr_t>::value << std::endl;
}
