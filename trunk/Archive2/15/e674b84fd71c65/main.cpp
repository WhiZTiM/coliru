#include <iostream>

class Foo
{
    int val{42};
    public:
    inline auto get()
    {
        return val;
    }
};
     
int main() {
    Foo f;
    f.get();
    std::cout << "Still alive!";
    return 0;
}
