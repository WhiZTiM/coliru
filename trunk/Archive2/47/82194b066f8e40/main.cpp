#include <algorithm>
#include <vector>

template<class T>
class Point
{
};

template<class T>
class FeatureGeneric
{
};

template<class T>
class FeaturePoint : public FeatureGeneric<T>
{
};

int main()
{
    FeaturePoint<Point> fp;
}