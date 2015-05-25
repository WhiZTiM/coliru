#include <experimental/optional>

int main()
{
    namespace stdx = std::experimental;
    stdx::optional<stdx::optional<int>> o = stdx::nullopt;
}
