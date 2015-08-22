#include <iostream>
#include <string>
#include <vector>

struct Test
{
    union { std::string str_; };
};

int main()
{
    Test t;
    t.str_ = "Hello World";
    std::cout << t.str_ << std::endl;
    return 0;
}
