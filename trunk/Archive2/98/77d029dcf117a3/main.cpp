#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <functional>

using void_f = void();
struct toy {
    void_f bob;
};
void toy::bob() {
    std::cout << "hello bob\n";
}

int main()
{
    toy{}.bob();
}
