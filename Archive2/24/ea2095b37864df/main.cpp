#include <chrono>
#include <iostream>
#include <future>

using std::cout;
using std::cin;
using std::endl;

int bar() { return 42; }

int main()
{
    {
        auto s1 = std::chrono::steady_clock::now();
        std::packaged_task<int()> pt1(bar);
        auto e1 = std::chrono::steady_clock::now();
    
        auto s2 = std::chrono::steady_clock::now();
        auto sh_ptr1 = std::make_shared<std::packaged_task<int()> >(bar);
        auto e2 = std::chrono::steady_clock::now();
    
    }
    
    constexpr int n = 1000;

    auto s1 = std::chrono::steady_clock::now();
    for (int i = 0; i != n; ++i)
        std::packaged_task<int()> pt1(bar);
    std::packaged_task<int()> pt1(bar);
    auto e1 = std::chrono::steady_clock::now();

    auto s2 = std::chrono::steady_clock::now();
    for (int i = 0; i != n; ++i)
        auto sh_ptr1 = std::make_shared<std::packaged_task<int()> >(bar);
    auto sh_ptr1 = std::make_shared<std::packaged_task<int()> >(bar);
    auto e2 = std::chrono::steady_clock::now();

    auto first = std::chrono::duration_cast<std::chrono::nanoseconds>(e1-s1);
    auto second = std::chrono::duration_cast<std::chrono::nanoseconds>(e2-s2);

    cout << "Regular: " << first.count() / (double) n << endl
         << "Make shared: " << second.count() / (double) n << endl;

    pt1();
    (*sh_ptr1)();

    cout << "As you can see, both are working correctly: " 
         << pt1.get_future().get() << " & " 
         << sh_ptr1->get_future().get() << endl;

    return 0;
}