#include <boost/variant.hpp>

enum class Type { W, X, Y, Z };

struct A {};

struct B
{
	B(int) {}
};

struct C
{
	C(int, int) {}
};

using variant_t = boost::variant<A, B, C>;

template<typename... Args>
variant_t MakeVariantOverEnum(Type type, Args&&... args)
{
    switch (type)
    {
        case Type::X: return B(std::forward<Args>(args)...); break;
        case Type::Z: return C(std::forward<Args>(args)...); break;
        
        default:      return A(std::forward<Args>(args)...); break;
    }
}

// meant to be fully runtime
const Type GetTypeFromIO() { return Type::Z; }
const int GetFirstArgFromIO() { return 0; }
const int GetSecondArgFromIO() { return 0; }

int main()
{
    const Type type = GetTypeFromIO();
    const int firstArg = GetFirstArgFromIO();
    const int secondArg = GetSecondArgFromIO();    
    
    variant_t newVariant;
    
    if (firstArg != 0 && secondArg != 0) newVariant = MakeVariantOverEnum(type, firstArg, secondArg);
    else if (firstArg != 0)              newVariant = MakeVariantOverEnum(type, firstArg);
    else                                 newVariant = MakeVariantOverEnum(type);
}
