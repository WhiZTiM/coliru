#include <iostream>
#include <vector>
#include <memory>

struct Test
{
    Test() { }
    ~Test() { }
    Test(Test &&) { }
    Test &operator =(Test &&) { return *this; }

    Test(const Test &) = delete;
    Test &operator =(const Test &) = delete;
};

int main()
{
    std::vector<Test> vt;
    vt.resize(256);
    std::cout << "compilation succeeded." << std::endl;
}
