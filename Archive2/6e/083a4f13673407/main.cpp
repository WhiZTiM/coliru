#include <cmath>

namespace gqm
{

template <typename T>
struct vector2 {
    vector2() {}
    vector2(T x, T y) : x(x), y(y) {}
    vector2 operator*(float s) const
    {
        return vector2(x * s, y * s);
    }
    T x;
    T y;
};


//it works good!
//template <typename T>
//inline T operator*(float s,const T &t)
//{
//    return t.operator*(s);
//}

//it do not works!Why?
template <typename T>
inline T operator*(float s,const T &t)
{
    return t*s;
}

typedef vector2<float> vec2;

}//namespace gqm

int main()
{
    gqm::vec2 v2 = 0.5 * gqm::vec2(1.0,1.0);

    return 0;
}