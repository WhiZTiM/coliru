#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>

using namespace std;

enum class LogLevel {
    Critical,
    Error,
    Warning,
    Notice,
    Debug,
    Trace
};

#define DEBUG Warning

std::ostream& operator<<(std::ostream &os, LogLevel l)
{
    switch(l) {
        case LogLevel::Critical: return os << "Critical";
        case LogLevel::Error: return os << "Error";
        case LogLevel::Warning: return os << "Warning";
        case LogLevel::Notice: return os << "Notice";
        case LogLevel::Debug: return os << "Debug";
        case LogLevel::Trace: return os << "Trace";
        default: return os << static_cast<int>(l);
    }
}
        
int main(...)
{
    std::cout << "Critical is " << LogLevel::Critical << std::endl;
    std::cout << "Debug is " << LogLevel::Debug << std::endl;
    std::cout << "DEBUG is " << LogLevel::DEBUG << std::endl;
}