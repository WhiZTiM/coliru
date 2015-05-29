#include <memory>

using namespace std;

int main()
{
    unique_ptr<int> foo(new int(22));
    foo.reset(new int(44));
    foo(new int(88));
}
