#include <iostream>
#include <string>
#include <vector>

class Q
{
public:
    Q(int i) {}
};

class I : public Q {};

class C : public virtual I
{
public:
    C(int i): Q(i) {}
};

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
}
