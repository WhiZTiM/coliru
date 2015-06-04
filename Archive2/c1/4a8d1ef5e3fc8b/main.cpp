#include <iostream>
#include <string>
#include <vector>


void
fun_with_lambdas()
{
    unsigned int counter = 555;
    auto parent = [counter = 10]() mutable {
        auto child = [&counter]() {
            std::cout << "child counter: " << counter << std::endl;
        };
        ++counter;
        child();
    };
    auto parent2 = [counter = std::string("potato")]() {
        std::cout << "I like " << counter << std::endl;
    };
    parent();
    std::cout << "counter: " << counter << std::endl;
    parent();
    std::cout << "counter: " << counter << std::endl;
    parent();
    std::cout << "counter: " << counter << std::endl;
    parent2();
}

int main()
{
    fun_with_lambdas();
    std::cout << "Done" << std::endl;
}
