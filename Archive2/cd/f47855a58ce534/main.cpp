#include <cstdlib>
#include <iostream>

[[ noreturn ]] void f() {
throw "error";
// OK
}
[[ noreturn ]] [[deprecated("broken")]] void q(int i) {
// behavior is undefined if called with an argument <= 0
if (i > 0)
throw "positive";
}

[[deprecated]]
int globalIndex;

[[made_by_me("cause",f)]] alignas(1024)
int main()
{
    std::cout << "Test" << std::endl;
    int i = 0;
    f();
    std::cout << i << "Shouldn't happen" << std::endl;
}