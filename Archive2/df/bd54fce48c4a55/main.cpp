
#include <iostream>
class Coordinate
{
public:
    int w, x, y, z;
    Coordinate(int w) 
    { 
        printf("Call 1D\n"); 
        this->w = w;
    }
    Coordinate(int w, int x) : Coordinate(w)
    { 
        printf("Call 2D\n");
        this->x = x; 
    }
    Coordinate(int w, int x, int y) : Coordinate(w,x) 
    { 
        printf("Call 3D\n");
        this->y = y;
    }
    Coordinate(int w, int x, int y, int z) : Coordinate(w, x, y)
    {
        printf("Call 4D\n");
        this->z = z; 
    }
};

int main(int argc, char** argv)
{
    Coordinate c(1, 2, 3, 4);
}