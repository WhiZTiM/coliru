#include <iostream>
char x;
struct Outer {
    class Inner {
    public:
        const static int i = sizeof(x);
    };
    const static int i = sizeof(x);
    long x;
};
int main()
{
    std::cout << Outer::Inner::i << '\n';
}
