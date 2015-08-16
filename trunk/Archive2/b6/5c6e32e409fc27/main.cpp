#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <sstream>

std::vector<std::string> messages[2];

void func1 (int thid)
{
    int local = 10;
    static int st = 100;


    std::ostringstream msg;
    msg << "thid: " << thid << " local is @" << std::hex << &local << std::endl;
    msg << "thid: " << thid << " static is @" << std::hex << &st << std::endl;
    messages[thid].push_back(msg.str());

}

void func2 (int thid)
{
    int a[42];
    std::ostringstream msg;
    msg << "thid: " << thid << " a is @" << std::hex << &a << std::endl;
    messages[thid].push_back(msg.str());
    func1 (thid);
}

int main()
{
    std::thread t1 (func1, 1);  //Execute func1 on thread "1"...
    func1(0);                   //...And then do the same on current (main) thread "0"

    t1.join();

    for (int i = 0; i < 2; ++i)
    {
        std::cout << "THREAD " << i << ":" << std::endl;
        for (auto const &msgs : messages[i])
            std::cout << msgs;
    }
    return 0;
}

