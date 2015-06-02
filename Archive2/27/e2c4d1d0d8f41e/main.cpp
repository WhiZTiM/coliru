//#include <random>
//#include <cassert>
#include <iostream>
#include <iomanip>
//#include <typeinfo>
//#include <map>
//#include <algorithm>

#include <random>
#include <cassert>

class RandomGenerator
{
private:
    static std::random_device _randomDevice;
    std::mt19937 _seededEngine;
    
public:
    RandomGenerator()
    : _seededEngine(_randomDevice())
    {
        std::cout << "!" << std::endl;
    }
    
    RandomGenerator(const RandomGenerator&) = default;
    RandomGenerator(RandomGenerator&) = default;
    RandomGenerator(RandomGenerator&&) = default;
    
    template <typename Seed>
    RandomGenerator(Seed&& seed)
    : _seededEngine(std::forward<Seed>(seed))
    {
    }
    
    ~RandomGenerator()
    {
    }
    
    template <typename T, typename std::enable_if<std::is_integral<T>::value>::type* = nullptr>
    T getNext(T minIncluded, T maxIncluded) //[min, max]
    {
        return getNext<T, std::uniform_int_distribution<T>>(minIncluded, maxIncluded);
    }
    
    template <typename T, typename std::enable_if<std::is_floating_point<T>::value>::type* = nullptr>
    T getNext(T minIncluded, T maxIncluded) //[min, max]
    {
        return getNext<T, std::uniform_real_distribution<T>>(minIncluded, maxIncluded);
    }
    
private:
    template <typename T, typename TDistribution>
    T getNext(T min, T max)
    {
        assert(min <= max);
        TDistribution distribution(min, max);
        return distribution(_seededEngine);
    }
};

std::random_device RandomGenerator::_randomDevice;


float getFloat(float min, float max)
{
    float r = (float)rand()/(float)RAND_MAX;
    return min + r*(max-min);
}

int getInt(int min, int max)
{
    if(max == min)
    {
        return max;
    }
    else if(max < min)
    {
        // swap values
        min ^= max;
        max ^= min;
        min ^= max;
    }
    return min + (rand() % (int)(max - min + 1));
}

std::string getString(size_t length, RandomGenerator& mainRandomGenerator)
{
    static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string str(length, 0);
    for (size_t i = 0; i < length; ++i)
    {
        size_t pos = mainRandomGenerator.getNext<size_t>(0, sizeof(charset)-2);
        str.at(i) = charset[pos];
    }
    return str;
}


int main() 
{
    RandomGenerator rg;    
    std::cout << getString(120, rg) << std::endl;
    
    void* v = nullptr;
    int* i0 = static_cast<int*>(v);
    (void) i0;
    
    double* d1 = nullptr;
    int* i1 = static_cast<int*>(d1); //peta
    (void)i1;
    
    double* d2 = nullptr;
    int* i2 = reinterpret_cast<int*>(d2); //se lo traga.
    (void)i2;
    
    /*
    std::cout << std::setprecision(std::numeric_limits<long double>::digits10 + 1) << std::endl;
    
    float highestDouble = std::numeric_limits<float>::max();
    float min = std::nextafter(0.0, highestDouble);
    float max = std::nextafter(min, highestDouble);
    std::cout << "min: " << min << std::endl;
    std::cout << "max: " << max << std::endl;
    std::cout << std::endl;
    
    for (int i=0; i<100; ++i)
    {
        std::cout << getFloat(min, max) << std::endl;
    }
    std::cout << std::endl;
    
    for (int i=0; i<100; ++i)
    {
        std::cout << getInt(0, 1) << std::endl;
    }
    std::cout << std::endl;
    
    for (int i=0; i<100; ++i)
    {
        std::cout << rg.getNext(min, max) << std::endl;
    }
    std::cout << std::endl;
    
    for (int i=0; i<100; ++i)
    {
        std::cout << rg.getNext(3, 2) << std::endl;
    }
    std::cout << std::endl;
    
    RandomGenerator rg2 = rg;
    
    std::cout << rg.getNext(min, max) << std::endl;
    std::cout << rg2.getNext(min, max) << std::endl;
    std::cout << rg.getNext(min, max) << std::endl;
    std::cout << rg2.getNext(min, max) << std::endl;
    std::cout << rg.getNext(min, max) << std::endl;
    std::cout << rg2.getNext(min, max) << std::endl;*/
}