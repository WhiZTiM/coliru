#include <cstdint>
#include <cstring>
#include <iomanip>
#include <iostream>

#define PRINT_LOCATION() \
    std::cout << std::setw(22) << __PRETTY_FUNCTION__                   \
      << " at offset " << std::setw(2)                                  \
        << (reinterpret_cast<char const*>(this) - addr)                 \
      << " ; data is at offset " << std::setw(2)                        \
        << (reinterpret_cast<char const*>(&dummy) - addr)               \
      << " ; naively to offset "                                        \
        << (reinterpret_cast<char const*>(this) - addr + sizeof(*this)) \
      << "\n"

struct l0 {
    std::int64_t dummy;
    
    void report(char const* addr) { PRINT_LOCATION(); }
};

struct l1 : virtual l0 {
    std::int64_t dummy;
    
    void report(char const* addr) { PRINT_LOCATION(); l0::report(addr); }
};

struct l2 : virtual l0, virtual l1 {
    std::int64_t dummy;
    
    void report(char const* addr) { PRINT_LOCATION(); l1::report(addr); }
};

struct l3 : l2, virtual l1 {
    std::int64_t dummy;
    
    void report(char const* addr) { PRINT_LOCATION(); l2::report(addr); }
};

void print_range(void const* b, std::size_t sz)
{
    std::cout << "[" << (void const*)b << ", "
              << (void*)(reinterpret_cast<char const*>(b) + sz) << ")";
}

void my_memcpy(void* dst, void const* src, std::size_t sz)
{
    std::cout << "copying from ";
    print_range(src, sz);
    std::cout << " to ";
    print_range(dst, sz);
    std::cout << "\n";
}

int main()
{
    l3 o{};
    o.report(reinterpret_cast<char const*>(&o));
    
    std::cout << "the complete object occupies ";
    print_range(&o, sizeof(o));
    std::cout << "\n";
    
    l1& so = o;
    l1 t;
    my_memcpy(&t, &so, sizeof(t));
}