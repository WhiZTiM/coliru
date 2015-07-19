#include <iostream>
#include <thread>
#include <functional>

void dummyTask(int limit)
{
    for (int i=0; i<limit; i++)
    {
        std::cout << "X";
    }
}

void anotherDummyTask(int beginAt)
{
    for(int i=beginAt; i>=0; i--)
    {
        std::cout << "Y";
    }
}

int main()
{
    std::thread th1{dummyTask, 5};
    std::thread th2{anotherDummyTask, 5};

    th1.join();
    th2.join();

    return 0;
}


