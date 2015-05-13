#include <iostream>
#include <string>
#include <vector>

    struct vector2d
    {
    	float x, y;

		explicit vector2d(float ix, float iy) : x(ix), y(iy) { }

		/*friend*/ const vector2d operator + (const vector2d& v1, const vector2d& v2) {
			return vector2d(v1.x + v2.x, v1.y + v2.y);
		}
		// ... a lot of other code here ...
    };
                
int main() {

    vector2d a(1, 2);
	vector2d b(3, 4);

	vector2d c = a + b;
    
}