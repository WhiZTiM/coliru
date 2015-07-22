#include <memory>    // for std::unique_ptr
#include <utility>   // for std::move
#include <vector>    // for std::vector

struct bar {};
using vtype = std::vector<std::unique_ptr<bar>>;

struct foo
{
    foo(vtype v) : _v(std::move(v)) { }
private:
    vtype _v;
};

vtype getVector()
{
    vtype v;
    v.push_back(std::unique_ptr<bar>(new bar()));
    return v;
}  

int main()
{
    foo f(std::move(getVector()));
}
