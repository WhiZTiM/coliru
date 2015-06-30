#include <iostream>
#include <chrono>
using namespace std;
int main()
{
    chrono::high_resolution_clock highResClock;
    chrono::duration<int, ratio<1, 1> > dur(1);
    chrono::time_point<chrono::high_resolution_clock> end = highResClock.now() + dur;

    while (highResClock.now() < end)
    {
        std::cout << "boo\n";
        break;
    }
}
