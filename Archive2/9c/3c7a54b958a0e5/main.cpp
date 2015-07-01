#include <utility>
#include <sstream>
#include <ctime>

using namespace std;
typedef int ElogLevel;

struct logline_t
{
    stringstream logString; /*!< String line to be saved to a file (and printed to cout). */
    ElogLevel logLevel; /*!< The \ref ElogLevel of this line. */
    timeval currentTime; /*!< time stamp of current log line */

    logline_t& operator =(const logline_t& a)
    {
        logString << a.logString.str();
        logLevel = a.logLevel;
        currentTime = a.currentTime;

        return *this;
    }
};
    
int main() {
}