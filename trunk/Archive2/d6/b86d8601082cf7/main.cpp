#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <atomic>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

using namespace std;

void hello_world()
{
    cout << "Hello World!" << endl;
}

int main()
{
    
    std::thread t1(hello_world);
    
    cout << "Thread started." <<endl;

    t1.join();
    
    return 0;
}

