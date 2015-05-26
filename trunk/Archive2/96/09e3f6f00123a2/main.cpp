#include <random>
#include <cassert>
#include <iostream>

struct AttrValue {
public:
    template<typename T>
    AttrValue(T&& value) :
        ptr(new AttrValueDerived<T>(std::forward<T>(value))) {
    }

private:
    class AttrValueBase {
        pu
        virtual ~AttrValueBase() = default;
    };

    template<typename T>
    class AttrValueDerived : AttrValueBase {
        T value;
        
        AttrValueDerived(T&& value) :
            value(std::forward<T>(value)) {
        }
    };

    AttrValueBase* ptr;
};

int main() 
{
    AttrValue attr(32.1);
    std::cout << attr.value << std::endl;
}
