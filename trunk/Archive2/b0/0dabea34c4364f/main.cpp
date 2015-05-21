#include <iostream>
#include <chrono>

class LogTimer {
    std::string str;
    std::chrono::high_resolution_clock::time_point m_start;
public:
    LogTimer(const std::string& file, int i)
        : m_start(std::chrono::high_resolution_clock::now())
    {
        str = file + ':' + std::to_string(i);
    }
    
    ~LogTimer() {
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>
                    (end - m_start).count();
        std::cout << str << " [" << duration << "µs]\n";
    }
    
    LogTimer& operator<<(const std::string& p) {
        str += '[' + p + ']';
        return *this;
    }
};

namespace Logger {
    LogTimer Timer(const std::string& f, int i) {
        return LogTimer(f, i);
    }
}

//#define LOG_SCOPE_TIME LogTimer ___t = Logger::Timer(__FILE__,__LINE__)
#define LOG_SCOPE_TIME LogTimer ___t = Logger::Timer(__FILE__,__LINE__); ___t

int main() 
{
    LOG_SCOPE_TIME << "something";
}