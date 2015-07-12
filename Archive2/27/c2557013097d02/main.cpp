#include <iostream>

using namespace std;

// Abstract super class 'Shape'
class Shape{
    
    public:
    
        virtual bool intersect(Shape& rhs) = 0;
};

// Point (in 2D space)
template <class T>
class Point{
    
    private:
        T x_;
        T y_;
        
    public:
        Point() : x_(0), y_(0) {}
        Point(T x, T y) { x_ = x; y_ = y;}      
        
};

// Circle (in 2D space)
template <class T>
class Circle : public Shape{
    
    private:
        Point<T> center_;
        T radius_;
        
    public:
        Circle() : center_(0), radius_(1) {}
        Circle(const Point<T>& center, T radius) : center_(center), radius_(radius) {}
        
        virtual bool intersect(Shape& rhs) {
            return rhs.intersect(*this);
        }
};

// Line (in 2D space)
template <class T>
class Line : public Shape{
    
    private:
        Point<T> begin_;
        Point<T> end_;
        
    public:
        Line() : begin_(0, 0), end_(1, 1) {}
        Line(const Point<T>& begin, const Point<T>& end) : begin_(begin), end_(end) {}
        
        virtual bool intersect(Shape& rhs) {
            return rhs.intersect(*this);
        }
};

bool intersect(Shape& s1, Shape& s2){
    s1.intersect(s2);
}

int main(int argc, char* argv[]) {


    return 0;
} 