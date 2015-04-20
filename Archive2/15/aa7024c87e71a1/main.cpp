#include <list>

class Walker {
    public:
        Walker(int); 
        ~Walker(); 

        double *x; 
        double *y; 
        double *z; 
        double weight; 
        int molteplicity; 
};

Walker::Walker(int particle_num) {
    x = new double[particle_num];
    y = new double[particle_num];
    z = new double[particle_num];
}

Walker::~Walker() {
    delete[] x;
    delete[] y;
    delete[] z;
}

int main() {
    std::list<Walker> population {Walker(1), Walker(2), Walker(3), Walker(0)};
    for (auto it = population.begin(); it != population.end();) {
        if( it->molteplicity == 0 ) {
            it = population.erase(it);
        } else {
            ++it;
        }
    }
}