#include <memory>
#include <vector>

class FooImpl {};

class Foo
{
    std::unique_ptr<FooImpl> myImpl;
public:
    Foo( Foo&& f ) = default;
    Foo& operator=( Foo&& f) = delete;
    Foo(){}
    ~Foo(){}
};

int main() {
    std::vector<Foo> testVec;
    testVec.resize(10);
    return 0;
}
