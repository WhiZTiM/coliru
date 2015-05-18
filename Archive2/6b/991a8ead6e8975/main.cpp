#include <memory>
#include <iostream>

void process(std::shared_ptr<int> ptr)
{
    std::cout << "in process: " << ptr.use_count() << std::endl;
}

int main()
{
    std::shared_ptr<int> p(new int(42));
    process(std::shared_ptr<int>(p.get()));
    std::cout << "exit main" << std::endl;
}
