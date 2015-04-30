#include <list>
#include <future>
#include <stack>

struct listPart
{
    std::list<int> data;
    std::promise<std::list<int>> p;
};

std::stack<listPart> stff;
listPart newLowerPart;

int main() {
    stff.push(std::move(newLowerPart));
}