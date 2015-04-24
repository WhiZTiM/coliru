#include <iostream>
#include <cmath>

    template<class Vector2D,class TimeType>
	class LinearMotionOfUniformAcceleration2D
	{
	private:
		const Vector2D dpt;
		const Vector2D dst;
		const TimeType term;
	public:
		LinearMotionOfUniformAcceleration(const Vector2D& _start_point, const Vector2D& _end_point, TimeType _dt)
			:dpt(_start_point), dst(_end_point), term(_dt){}
		Vector2D v0(void) const
		{
			return Vector2D((dst - dpt).x() * (2 / term), (dst - dpt).y() * (2 / term));
		}
		Vector2D a(void) const
		{
			return Vector2D((dst - dpt).x() * (-2 / std::pow(term, 2)), (dst - dpt).x() * (-2 / pow(term, 2)));
		}
	};

int main(int argc, char** argv)
{
    
    return 0;
}

