#include <utility>

class C {
    typedef std::pair<double, double> Point;
public:
    Point get_point() const {
        return {};
    }
}; 

int main() {
    auto point = C{}.get_point();
}