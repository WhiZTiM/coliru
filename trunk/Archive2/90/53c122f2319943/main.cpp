#include <tuple>
#include <utility>

struct Foo
{
};

template <typename... Args>
void start(Args&&... args) {
    auto x = [args = std::make_tuple(std::forward<Args>(args)...)] () mutable {
            auto y = [args] () mutable {
                auto z = [] (Args&&... args) {
                    return new Foo(std::forward<Args>(args)...);
                };
            };
    };
}

int main()
{
    start(Foo{});
}