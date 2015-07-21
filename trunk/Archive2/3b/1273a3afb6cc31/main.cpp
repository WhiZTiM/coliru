#include <iostream>
#include <functional>
#include <type_traits>

int main()
{
    std::system_error error(EPERM, std::system_category(), "Failed to set the system clock");
    std::cout << error.what() << std::endl;
}
