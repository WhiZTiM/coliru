#include <type_traits>

class float16 {
public:
    operator float() {
        return 0;
    }
    
    operator double() {
        return 0;
    }
};

static_assert(std::is_same<std::common_type<float16, float>::type, float>::value,
    "common type is not float");
static_assert(std::is_same<std::common_type<float16, double>::type, double>::value,
    "common type is not double");

int main() {
}