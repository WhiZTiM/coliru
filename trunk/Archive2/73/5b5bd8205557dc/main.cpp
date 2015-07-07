#include <iostream>
#include <memory>

int main()
{
    auto ptr = std::make_shared<int>(1);
    std::cout << "!ptr: "  << std::noboolalpha << !ptr << ' ' << std::boolalpha << !ptr << std::endl;
    std::cout << "!!ptr: "  << std::noboolalpha << !!ptr << ' ' << std::boolalpha << !!ptr << std::endl;
    std::cout << "~!!ptr: "  << std::noboolalpha << ~!!ptr << ' ' << std::boolalpha << static_cast<bool>(~!!ptr) << std::endl;
    auto null = decltype(ptr)();
    std::cout << "!null: "  << std::noboolalpha << !null << ' ' << std::boolalpha << !null << std::endl;
    std::cout << "!!null: "  << std::noboolalpha << !!null << ' ' << std::boolalpha << !!null << std::endl;
    std::cout << "~!!null: "  << std::noboolalpha << ~!!null << ' ' << std::boolalpha << static_cast<bool>(~!!null) << std::endl;
}
