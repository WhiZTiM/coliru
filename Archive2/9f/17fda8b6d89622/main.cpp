#include <string>
#include <functional>

struct int_holder {
    int value;
    int triple() {return value*3;}
};

int main(int argc, const char * argv[])
{
    std::string abc{"abc"};
    int_holder one{1};

    auto f1 = std::mem_fn(&std::string::clear);
    auto f2 = std::mem_fn(&int_holder::triple);
    f1(abc);
    f2(one);
}