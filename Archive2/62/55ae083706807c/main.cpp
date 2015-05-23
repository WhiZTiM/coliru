#include <iostream>
#include <string>
#include <vector>

struct Timer
{
    std::string timerName;
    std::string timerRef;
};

int main()
{
    int n { 1 };
    const Timer t = [&]() {
        Timer result;
        if (n == 1)
        {
            result = { "Timer 1", "Timer Ref 1" };
        }
        else
        {
            result = { "Timer 2", "Timer Ref 2" };
        }
        return result;
    }();
    //t.timerName = "New Timer"; /* invalid due to constness, correct */
    std::cout << t.timerName << std::endl;
}
