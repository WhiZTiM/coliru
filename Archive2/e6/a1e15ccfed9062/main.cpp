#include <iostream>
#include <string>
#include <vector>

    struct vector2d
    {
        float x, y;

		explicit vector2d(float ix, float iy) : x(ix), y(iy) {}

		vector2d operator+(const vector2d& v)
        {
			return vector2d(x + v.x, y + v.y);
		}
		// ... a lot of other code here ...
    };
                
int main() {

    vector2d a(1, 2);
	vector2d b(3, 4);

	vector2d c = a + b;
    
}