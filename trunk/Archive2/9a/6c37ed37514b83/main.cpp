#include <vector>
#include <functional>
#include <iterator>

using Work = std::vector<std::function<void()>>;
void begin(Work const& work) {
    for(auto& f : work)
        f();
}// begins the work

void test(Work work) {
    begin(work); // dammit why don't it start the work
}

#include <iostream>

int main() {
    Work w { []{std::cout << "Running\n";}, []{std::cout << "Bye\n";}, };
    test(w);
}
