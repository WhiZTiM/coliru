#include <type_traits>

struct Widget {};

int main()
{
    Widget w;
    const Widget& cw = w;
    auto& myWidget1 = cw;
    
    static_assert(std::is_same<decltype(myWidget1), const Widget&>{}, "!");
}
