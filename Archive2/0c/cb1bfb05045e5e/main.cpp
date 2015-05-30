#include <iostream>
#include <mutex>
#include <sstream>


// Thread-safe printing to std::cout
// Usage example: Log() << "message";
struct Log : std::ostringstream {
    ~Log() {
        static std::mutex mutex;
        auto s = str();
        std::lock_guard<std::mutex> lock(mutex);
        std::cout << s;
    }
};


int main()
{
    Log() << "Test";
}

