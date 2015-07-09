#include <memory>
#include <vector>

class C
{
public:
    void Insert(std::vector<std::unique_ptr<int>> ) {}
};

int main()
{
    std::vector<std::unique_ptr<int>> v;

    C c;

    c.Insert(v);
}
