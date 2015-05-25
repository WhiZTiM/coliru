#include <iostream>
#include <memory>

struct A : std::enable_shared_from_this<A> { ~A() { std::cout << "DESTROYED\n"; } };

int main()
{
    A nonown;
    auto p = nonown.shared_from_this();
    std::cout << p.use_count() << "\n";
}