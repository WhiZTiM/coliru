#include <iostream>

struct point2d {
    int x;
    int y;
};

int main() {
    point2d myPoint;
    
    myPoint.x = 1;
    myPoint.y = 2;
    
    std::cout << "myPoint.x: " << myPoint.x << std::endl;
    
    return 0;
}