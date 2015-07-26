#include <chrono>
#include <iostream>
#include <limits>
#include <memory>

template <typename... Args>
auto test(Args&&... args) {
    using clock = std::chrono::high_resolution_clock;
    auto best = clock::duration::max();

    for (int outer = 1; outer < 10000; ++outer) {
        auto now = clock::now();

        for (int inner = 1; inner < 20000; ++inner)
            std::shared_ptr<int> sh(std::forward<Args>(args)...);

        auto time = clock::now()-now;
        if (time < best) {
            best = time;
            outer = 1;
        }
    }

    return best.count();
}

int main()
{
    int j;

    test(std::shared_ptr<void>(), &j) ;
    //test(&j, [] (auto) {});
}
