#include <iostream>
#include <string>
#include <vector>

void do_something(int) {}

void fun (const std::vector<int> &vec) {
    for (int i = 0; i < vec.size() - 1; ++i)
        do_something(vec[i]);
}

int main()
{
    std::vector<int> foo;
}
