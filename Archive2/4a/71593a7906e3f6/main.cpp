#include <iostream>
#include <thread>
#include <future>
#include <memory>

using std::cout;
using std::cin;
using std::endl;

unsigned long long int factorial(unsigned long long int num)
{
    unsigned long long int N = num;
    for (unsigned long long int i = num; i > 1; --i)
    {
        num *=(--N);
    }

    return num;
}

int main()
{

    std::shared_ptr<std::packaged_task<int()> > ptr(new std::packaged_task<int()>(std::bind(factorial, 6)));
    std::future<int> fu1 = ptr->get_future();
    std::function<void()> task1 = [&ptr](){ ptr->operator()(); };

    std::packaged_task<int()> t(std::bind(factorial, 5));
    std::future<int> fu2 = t.get_future();
    std::function<void()> task2 = [&t](){ t(); };

    std::thread threads[2];

    threads[0] = std::thread(task1);
    threads[1] = std::thread(task2);

    cout << fu1.get() << endl;
    cout << fu2.get() << endl;

    threads[0].join();
    threads[1].join();

    return 0;
}