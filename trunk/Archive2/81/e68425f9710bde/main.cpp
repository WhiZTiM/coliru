#include <iostream>
#include <string>
#include <map>
#include <random>

int custom_random(int min, int max, int step) {
    static std::random_device rd;
    std::uniform_int_distribution<int> dist(min, max + step - 1);
    return dist(rd) / step * step;
}


 
int main()
{
    int min = 100;
    int max = 200;
    int bb = 5;
    
    for(int idx = 0; idx < 100; ++idx) {
        std::cout << custom_random(min, max, bb) << "\n";
    }
}