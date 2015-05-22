#include <iostream>
#include <string>
#include <vector>

void do_something(int);

void fun (const std::vector<int> &vec) {
    for (std::size_t i = 0; i < vec.size() - 1; ++i)
        do_something(vec[i]);
}

int main()
{
    std::vector<int> foo;
    for(std::size_t i = foo.size(); i >= 0; --i)
        std::cout << "asdf\n";
}
