#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <sstream>

std::vector<std::string> messages[2];

void thread_func (int thid)
{
    int local = 10;
    static int st = 100;


    std::ostringstream msg;
    msg << "thid: " << thid << " local is @" << std::hex << &local << std::endl;
    msg << "thid: " << thid << " static is @" << std::hex << &st << std::endl;
    messages[thid].push_back(msg.str());

}


int main()
{
    std::thread t1 (thread_func, 1);   //Execute func1 on thread "1"...
    thread_func(0);                           //...And then do the same on current (main) thread "0"

    t1.join();

    for (int i = 0; i < 2; ++i)
    {
        std::cout << "THREAD " << i << ":" << std::endl;
        for (auto const &msgs : messages[i])
            std::cout << msgs;
    }
    return 0;
}

