#include <vector>

static std::vector<int> v;

class C
{
    decltype(v.cbegin()) z = v.cbegin();
};

int main() {}