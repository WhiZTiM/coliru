#include <sstream>
#include <string>
#include <iostream>

using namespace std;

struct ElogLevel {};

struct logline_t
    {
        stringstream logString; /*!< String line to be saved to a file (and printed to cout). */
        ElogLevel logLevel; /*!< The \ref ElogLevel of this line. */
        timeval currentTime; /*!< time stamp of current log line */

        logline_t& operator =(const logline_t& a)
        {
            logString.str(a.logString.str());;
            logLevel = a.logLevel;
            currentTime = a.currentTime;

            return *this;
        }
    };

int main() {
    logline_t a;
    a.logString << "hello earth";
    logline_t b;
    b.logString << "hello mars";
    b = a;
    std::cout << b.logString.str() << std::endl;
    
}