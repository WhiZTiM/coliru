#include <memory>
#include <vector>

using namespace std;

class FooImpl {};

class Foo
{
   unique_ptr<FooImpl> myImpl;
public:
   Foo();
   ~Foo();
};

void Bar()
{
   vector<Foo> testVec;
   testVec.resize(10);
}

int main()
{
}
