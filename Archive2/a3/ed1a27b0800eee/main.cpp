#include <list>
#include <vector>

struct Walker {
    Walker(int num) 
        : x(num), y(num), z(num)
        , weight(0)
        , molteplicity(0)
        {}
        
    std::vector<double> x, y, z; 
    double weight; 
    int molteplicity; 
};    

int main() {
    std::list<Walker> population {Walker(1), Walker(2), Walker(3), Walker(0)};
    population.remove_if([](Walker const& w) { return w.molteplicity == 0; }); 
}