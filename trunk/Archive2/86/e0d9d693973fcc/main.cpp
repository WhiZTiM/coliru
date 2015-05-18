#include <iostream>
#include <memory>
#include <stack>

struct nocopy
{
    nocopy(int i) : i(i) {}
    nocopy(nocopy const&) = delete;
    nocopy& operator=(nocopy const&) = delete;
    int i;
};

std::ostream& operator<<(std::ostream& os, nocopy const& nc)
{
    os << nc.i;
    return os;
}

int main()
{
    auto original = std::make_shared<std::shared_ptr<nocopy>>(std::make_shared<nocopy>(5));
    auto other = std::make_shared<std::shared_ptr<nocopy>>(std::make_shared<nocopy>(6));
    std::stack<std::shared_ptr<std::shared_ptr<nocopy>>> todo;
    todo.push(original);
    auto temp = todo.top();
    todo.pop();
    *temp = *other;
    
    std::cout << **original << **other << **temp << std::endl;
}
