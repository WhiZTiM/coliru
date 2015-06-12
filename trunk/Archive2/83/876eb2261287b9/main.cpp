#include <unordered_map>
#include <vector>

struct A { std::unordered_map<std::string,std::string> x; std::size_t y; };

int main()
{
    std::vector<A> as;
    as.push_back({{}, 0 });
}