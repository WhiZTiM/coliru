#include <iostream>
#include <iomanip>
#include <utility>
 
template<typename... Items>
void print(const Items& ... items) {
    using discard = int[sizeof...(Items)];
    bool first = true;
    discard{((std::exchange(first, false) ? 0 : (std::cout << " ", 0)), std::cout << items, 0)...};
    std::cout << std::endl;
}
 
int main() {
    print("Any", "number of", "arguments", "(in this case:", 6, ")");
	print(1, 2, 3, 4, 5);
	print("Formatting works?", std::fixed, std::setprecision(5), 4.5);
	return 0;
}
