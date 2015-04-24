#include <future>
#include <iostream>
#include <thread>
#include <stdexcept>
 
int fib(int)
{
    throw std::runtime_error("It done broke");
}
 
int main()
{
    std::packaged_task<int(int)> fib_task(&fib); 
 
    std::cout << "starting task\n";
    auto result = fib_task.get_future();
    std::thread t(std::move(fib_task), 40);
 
    std::cout << "waiting for task to finish...\n";
    try
    {
        std::cout << result.get() << '\n';
    }
    catch (std::runtime_error const& m)
    {
        std::cout << "Exception: " << m.what() << '\n';
    }
 
    std::cout << "task complete\n";                                                                                                                                                                           
    t.join();
}