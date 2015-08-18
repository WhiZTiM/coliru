#include <type_traits>

static_assert(std::is_same<char, signed char>{} == false, "");
static_assert(std::is_same<char, unsigned char>{} == false, "");

#include <iostream>

int main()
{
    std::cout << "char is " << (std::is_signed<char>{} ? "signed" : "unsigned") << "\n";
}