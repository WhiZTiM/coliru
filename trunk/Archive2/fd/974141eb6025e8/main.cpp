#include <string>
#include <tuple>
using namespace std;

struct A
{
    const string name;

    A(string name) :name(name) {}
};

namespace {
    auto make_children() { return make_tuple(A("AA")); }
}

struct Parent 
{    
public:
    const decltype(make_children()) children{ make_children() };

    Parent()
    {

    }

};

int main()
{
    Parent p;
}
