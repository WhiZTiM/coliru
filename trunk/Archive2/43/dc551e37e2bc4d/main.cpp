#include <iostream>

//Definition
struct point2d {
    int x;
    int y;
};




//This is our operator to add together the X's and Y's for point2d
point2d operator+(point2d left, point2d right) {
    point2d result;
    result.x = left.x + right.x;
    result.y = left.y + right.y;
    
    return result;
}




int main() {
    point2d pointA = {1, 2};
    point2d pointB = {3, 4};

    std::cout << "pointA: (" << pointA.x << "," << pointA.y << ")" << std::endl;
    std::cout << "pointB: (" << pointB.x << "," << pointB.y << ")" << std::endl;
    
    //Let's use the new operator!
    point2d sumAB = pointA + pointB;
    
    std::cout << "pointA + pointB: (" << sumAB.x << "," << sumAB.y << ")" << std::endl;
    
    return 0;
}