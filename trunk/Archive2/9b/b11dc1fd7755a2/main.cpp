#include <iostream>
#include <cstdint>

namespace pm {
typedef uint64_t id_t;
namespace detail {
 
constexpr std::size_t stringLen(const char* str)
{
    return *str == '\0' ? 0 : 1 + stringLen(str + 1);
}
 
constexpr std::uint64_t exp(std::size_t base, std::size_t e)
{
	return e == 0 ? 1 : base * exp(base, e - 1);
}
 
constexpr id_t hashImpl(const char* str, std::size_t e)
{
	return *str == '\0' ? 0 : exp(31, e) * *str + hashImpl(str + 1, e - 1);
}
 
}
 
constexpr id_t hash(const char* str)
{
	return detail::hashImpl(str, detail::stringLen(str) - 1);
}
 
inline id_t hash(const std::string& str)
{
	return detail::hashImpl(str.c_str(), detail::stringLen(str.c_str()) - 1);
}
 
constexpr id_t operator "" _id(const char* str, std::size_t size)
{
	return detail::hashImpl(str, size - 1);
}
 
}

int main()
{
    using namespace pm;
    const auto myId = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ{}"_id;
    std::cout << myId << std::endl;
}