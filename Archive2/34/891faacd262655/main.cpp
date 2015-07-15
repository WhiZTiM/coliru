#include <vector>
#include <memory>
#include <iostream>

struct SomeThing{
    int a = 1;
};

class Foo{
public:

    std::vector<std::unique_ptr<SomeThing>> m_bar;
};

int main(int argc, char* argv[])
{
    Foo f;
    f = std::move(Foo());
    std::cout << "Success!" << std::endl;
    return 0;
}