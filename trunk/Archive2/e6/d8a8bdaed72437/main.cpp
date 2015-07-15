#include <boost/random/variate_generator.hpp>
#include <boost/generator_iterator.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real_distribution.hpp>

typedef boost::mt19937                     ENG;    // Mersenne Twister
typedef boost::random::uniform_real_distribution<> DIST;   // Uniform Distribution
typedef boost::variate_generator<ENG&,DIST> GEN;    // Variate generator

class RNG {

  private:
     ENG eng;
     DIST dist;

  public:
     GEN gen;
     RNG(double min,double max,int seed)
     : dist(min,max), gen(eng,dist)
     {eng.seed(seed); }
};

#include <ctime>
#include <iostream>

int main(){
    int myseed = std::time(nullptr);
    double minimum = 1.;
    double maximum = 10.;
    int N = 20;

    RNG myrn(minimum,maximum,myseed);

    for (int i = 0; i < N; i++){
        std::cout << myrn.gen() << std::endl;
    }
}
