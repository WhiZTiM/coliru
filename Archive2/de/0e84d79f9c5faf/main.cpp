#include <iostream>
#include <string>
#include <vector>


void
fun_with_lambdas()
{
    auto parent = [counter = 10]() mutable {
        auto child = [&counter]() {
            std::cout << "counter: " << counter << std::endl;
        };
        ++counter;
        child();
    };
    parent();
    parent();
    parent();
}

int main()
{
    fun_with_lambdas();
    std::cout << "Done" << std::endl;
}
