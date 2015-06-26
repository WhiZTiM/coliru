#include <string>
struct foo
{
    int a;
    std::string b;
    double c = 0.0;
};

int main()
{
    foo f{1,"hello"};
    foo f2{1,"world",5.0};

    return 0;
}
