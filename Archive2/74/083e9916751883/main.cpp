#include <type_traits>

//Init by field
struct POD{
    int a{};
    int b{};
    char c{};        
};

static_assert(std::is_pod<POD>::value, "OOPS");