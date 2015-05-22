#include <random>
#include <cassert>
#include <iostream>

//------------------------------------------ RandomGenerator.hpp ------------------------------------------

class RandomGenerator
{
private:
    static std::random_device _randomDevice;
    std::mt19937 _seededEngine;

public:
    RandomGenerator()
    : _seededEngine(_randomDevice())
    {        
    }
    
    template <typename Seed>
    RandomGenerator(Seed&& seed)
    : _seededEngine(std::forward<Seed>(seed))
    {
    }
    
    ~RandomGenerator()
    {
    }
    
    template <typename T, typename std::enable_if<std::is_integral<T>::value>::type* = nullptr>
    T getRandom(T min, T max) //[min, max]
    {
        assert(min <= max);
        std::uniform_int_distribution<T> distribution(min, max);
        return distribution(_seededEngine);
    }
    
    template <typename T, typename std::enable_if<std::is_floating_point<T>::value>::type* = nullptr>
    T getRandom(T min, T max) //[min, max)
    {
        assert(min <= max);
        std::uniform_real_distribution<T> distribution(min, max);
        return distribution(_seededEngine);
    }
};

std::random_device RandomGenerator::_randomDevice;

//------------------------------------------ RandomUtils.cpp ------------------------------------------

static RandomGenerator mainRandomGenerator;


int getInt(int min, int max)
{
#ifdef HYDRA_FAKE_RANDOM_INT
    return HYDRA_FAKE_RANDOM_INT;
#else
    return mainRandomGenerator.getRandom(min, max);
#endif
}

float getFloat(float min, float max)
{
#ifdef HYDRA_FAKE_RANDOM_FLOAT
    return HYDRA_FAKE_RANDOM_FLOAT;
#else
    if(min == max)
    {
        return min;
    }
    
    if(min > max)
    {
        std::swap(min, max);
    }
    
    return mainRandomGenerator.getRandom(min, max);
#endif
}

std::string getString(size_t len)
{
    static const char* charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string str(len, 0);
    for (size_t i = 0; i < len; ++i)
    {
        str.at(i) = charset[getInt(0, sizeof(charset)-1)];
    }
    return str;
}

//------------------------------------------ Little testing ------------------------------------------

int main() 
{
    for (int i = 0; i < 20; ++i)
    {
        std::cout << mainRandomGenerator.getRandom(0, 1) << " ";
    }
    std::cout << std::endl;
        
    for (int i = 0; i < 20; ++i)
    {
        std::cout << mainRandomGenerator.getRandom(0.2f, 0.2f) << " ";
    }
    std::cout << std::endl;
    
    for (int i = 0; i < 20; ++i)
    {
        std::cout << getInt(0, 10) << " ";
    }
    std::cout << std::endl;
    
    for (int i = 0; i < 20; ++i)
    {
        std::cout << getFloat(0.0f, 1.0f) << " ";
    }
    std::cout << std::endl;
    
    std::cout << getString(100) << std::endl;
}
