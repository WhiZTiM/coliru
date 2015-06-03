#include <iostream>

template<typename T> struct PointCloud {};
template<typename T> struct CvMat {};
template<typename T, typename U> struct Map {};

// Option 1, specialization by container type

template<typename T> struct P
{
    void compute(const T &d) { std::cout << "Using unspecialized compute" << std::endl; }
};

template<typename T> struct P<PointCloud<T> >
{
    void compute(const T &d) { std::cout << "using PointCloud specialization" << std::endl; }
};

template<typename T, typename U> struct P<Map<T,U> >
{
    void compute(const Map<T,U> &m) { std::cout << "using Map specialization" << std::endl; }
};

int main()
{    
    // Option 1
    P<PointCloud<int> > p1;
    p1.compute(0);
    
    P<Map<int,double> > p2;
    p2.compute(Map<int,double>());
    
    return 0;
}