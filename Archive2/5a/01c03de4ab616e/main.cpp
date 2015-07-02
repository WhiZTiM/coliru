#include <atomic> 

int main() { 
    int i;
    std::atomic<int*> a = {&i};
}