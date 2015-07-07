#include <iostream>
#include <memory>

int main()
{
    auto ptr = std::make_shared<int>(1);
    std::cout << "!ptr: " << !ptr << std::endl;
    std::cout << "!!ptr: " << !!ptr << std::endl;
    std::cout << "~!!ptr: " << ~!!ptr << std::endl;
    auto null = decltype(ptr)();
    std::cout << "!null: " << !null << std::endl;
    std::cout << "!!null: " << !!null << std::endl;
    std::cout << "~!!null: " << ~!!null << std::endl;
}
