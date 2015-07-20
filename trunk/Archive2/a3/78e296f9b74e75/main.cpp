#include <iostream>
#include <future>
#include <thread>

using std::future;
using std::async;
using std::move;

template <typename T, typename Work>
auto then(future<T> f, Work w) -> future<decltype(w(f.get()))>
{
    return async([](future<T> f, Work w)
                      { return w(f.get()); }, move(f), move(w));
}

template <typename Work>
auto then(future<void> f, Work w) -> future<decltype(w())>
{
    return async([](future<void> f, Work w)
                      { f.wait(); return w(); }, move(f), move(w));
}
 
int main()
{
    std::future<int> f = std::async([]{
        std::this_thread::sleep_for(std::chrono::microseconds(200));
        return 10;
    });

    auto f2 = then(std::move(f), [](int i){
        return 2 * i;
    });
    
    std::cout << f2.get() << std::endl;
}