#include <utility>
#include <sstream>
#include <ctime>
#include <iostream>

using namespace std;

struct logline_t
{
    stringstream logString; /*!< String line to be saved to a file (and printed to cout). */

    logline_t& operator =(const logline_t& a)
    {
        logString.str("");
        //logString << a.logString.str();
        logString << a.logString.rdbuf();
        return *this;
    }
};
    
int main() {
    logline_t l1;
    l1.logString << "hello";
    logline_t l2;
    logline_t l3;
    l2 = l1;
    l1.logString << "world";
    l3 = l1;
    // incorrectly outputs: l2: hello, l3: world
    // correct outpus: l2: hello, l3: helloworld
    std::cout << "l2: " << l2.logString.str() << ", l3: " << l3.logString.str() << std::endl;

}