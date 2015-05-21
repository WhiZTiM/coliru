#include <chrono>
#include <functional>
#include <iostream>

namespace Furrovine
{

    template <typename Clock = std::chrono::high_resolution_clock>
    struct scopewatch
    {
    public:
        typedef Clock clock;
        typedef typename clock::time_point time_point;
        typedef typename clock::duration duration;
        typedef typename clock::rep rep;
        typedef typename clock::period period;

    private:
        std::function<void(duration)> fx;
        time_point start;

    public:
        template <typename Fx>
        scopewatch(Fx f) : fx(f), start(clock::now()) { 
        }

        ~scopewatch() {
            fx(clock::now() - start);
        }
    };

    template <typename Clock = std::chrono::high_resolution_clock, typename Fx>
    scopewatch<Clock> make_scopewatch(Fx const & reportfunction) {
        return scopewatch<Clock>(reportfunction);
    }
}

int main() {
    auto rep = [](std::chrono::high_resolution_clock::duration t) { std::cout << "\nTime: " << t.count(); };
    auto watch = Furrovine::make_scopewatch(rep);
    for (int i = 0; i < 10; i++) {
        std::cout << "Tick\t";
    }
}
