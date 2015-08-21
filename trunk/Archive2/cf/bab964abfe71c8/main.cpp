#include <iostream>
#include <iostream>

struct point2d {
    int x;
    int y;
    
    point2d operator+(point2d right) {
        point2d result;
        result.x = x + right.x;
        result.y = y + right.y;
        
        return (result);
    }
};

point2d operator*(int left, point2d right) {
    point2d result;
    result.x = left * right.x;
    result.y = left * right.y;
    return result;
}

//Let's "cheat" a little by using our
//operator above!
point2d operator*(point2d left, int right) {
    return(right * left);
}

int main() {
    point2d pointA = {1,1};
    point2d pointB = {3,5};
    point2d sum = pointA + pointB;

    std::cout << "pointA: (" << pointA.x << "," << pointA.y << ")" << std::endl;
    std::cout << "pointB: (" << pointB.x << "," << pointB.y << ")" << std::endl;
    std::cout << "Sum: (" << sum.x << "," << sum.y << ")" << std::endl;
    
    //Now this will work.
    point2d multiplied_int = 2 * sum;
    
    std::cout << "2*sum: (" << multiplied_int.x << "," << multiplied_int.y << ")" << std::endl;
    
    return 0;
}