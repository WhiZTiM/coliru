#include <functional>
#include <memory>

int main()
{
    auto up = std::make_unique<int>(42);
    std::bind([](std::unique_ptr<int>&&){}, std::move(up));
}