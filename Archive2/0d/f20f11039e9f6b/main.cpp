#include <vector>

static std::vector<int> v;

#define DECL(a,b) decltype(b) a = b

class C
{
    DECL(a, v.cbegin());
};

int main() {}