#include <memory>
#include <iostream>

void func(std::shared_ptr<const int> p)
{
    std::cout << "Got " << *p << std::endl;
}

int main() {
    func(std::make_shared<int>(42));
}