#include <iostream>
#include <string>
#include <vector>
#include <queue>

struct A{
    bool compare (int, int) const {return true;}
};

int main()
{
    A a;
    auto comp = [&](int i, int i2) {return a.compare(i, i2);};
    std::priority_queue<int, std::vector<int>, decltype(comp)> q (comp);
}
