#include <random>

typedef std::mt19937                     ENG;    // Mersenne Twister
typedef std::uniform_real_distribution<> DIST;   // Uniform Distribution

class RNG {

  private:
     ENG eng;
     DIST dist;

  public:
     DIST::result_type gen() { return dist(eng); }
     RNG(double min,double max,int seed)
     : dist(min,max)
     {eng.seed(seed); }
};

#include <ctime>
#include <iostream>

int main(){
    auto myseed = std::random_device{}();
    double minimum = 1.;
    double maximum = 10.;
    int N = 20;

    RNG myrn(minimum,maximum,myseed);

    for (int i = 0; i < N; i++){
        std::cout << myrn.gen() << std::endl;
    }
}
