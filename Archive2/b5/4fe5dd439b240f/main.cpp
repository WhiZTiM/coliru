#include <iostream>
#include <string>
#include <vector>

struct vector2d
{
    float x, y;

	explicit vector2d(float ix, float iy) : x(ix), y(iy) {}

	vector2d operator+=(const vector2d& v)
    {
        x += v.x;
        y += v.y;
        return *this;
	}
	// ... a lot of other code here ...
};
    
vector2d operator+(vector2d v1, const vector2d& v2)
{
    v1 += v2;
    return v1;
}
                
int main() {

    vector2d a(1, 2);
	vector2d b(3, 4);

	vector2d c = a + b;
    
}