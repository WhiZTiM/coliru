#include <iostream>

template<class T>
class Point
{
};

template<class T>
class FeatureGeneric
{
public:
    virtual void compute() = 0;    
};

template<class T>
class FeaturePoint : public FeatureGeneric<T>
{
public:
    virtual void compute() { std::cout << "FeaturePoint::compute()" << std::endl; };
};

int main()
{
    FeaturePoint<Point<double>> fp;
    fp.compute();
}