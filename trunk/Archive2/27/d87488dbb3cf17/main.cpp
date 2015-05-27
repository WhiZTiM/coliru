#include <iostream>

struct MainType {
    ~MainType() {
        std::cout << "I quit!\n";
    }
};

int main() {
    int timesLooped = 0;
    const int maxTimes = 5;
    
    myLabel:
    MainType mt;
    ++timesLooped;
    if (timesLooped < maxTimes) {
        goto myLabel;
    }

    return 0;
}