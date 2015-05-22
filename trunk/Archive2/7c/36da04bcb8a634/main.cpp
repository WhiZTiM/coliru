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
    T getNext(T minIncluded, T maxExcluded) //[min, max)
    {
        return getNext<T, std::uniform_int_distribution<T>>(minIncluded, maxExcluded - 1);
    }
    
    template <typename T, typename std::enable_if<std::is_floating_point<T>::value>::type* = nullptr>
    T getNext(T minIncluded, T maxExcluded) //[min, max)
    {
        return getNext<T, std::uniform_real_distribution<T>>(minIncluded, maxExcluded);
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

//------------------------------------------ RandomUtils.cpp ------------------------------------------

static RandomGenerator mainRandomGenerator;


int getInt(int min, int max)
{
#ifdef HYDRA_FAKE_RANDOM_INT
    return HYDRA_FAKE_RANDOM_INT;
#else
    return mainRandomGenerator.getNext(min, max);
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
    
    return mainRandomGenerator.getNext(min, max);
#endif
}

std::string getString(size_t len)
{
    static const char* charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string str(len, 0);
    for (size_t i = 0; i < len; ++i)
    {
        str.at(i) = charset[getInt(0, sizeof(charset))];
    }
    return str;
}

//------------------------------------------ Little testing ------------------------------------------

int main() 
{
    for (int i = 0; i < 20; ++i)
    {
        std::cout << mainRandomGenerator.getNext(0, 2) << " ";
    }
    std::cout << std::endl;
        
    for (int i = 0; i < 20; ++i)
    {
        std::cout << mainRandomGenerator.getNext(0.2f, 0.21f) << " ";
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
    
    RandomGenerator seededRG(123456789);
int reproducibleRandomInt = seededRG.getNext(0, 100);
float reproducibleRandomFloat = seededRG.getNext(0.0f, 1.0f);

RandomGenerator randomRG;
int randomInt = randomRG.getNext(0, 100);
float randomFloat = randomRG.getNext(0.0f, 1.0f);

std::cout << reproducibleRandomInt << std::endl;
std::cout << reproducibleRandomFloat << std::endl;
std::cout << randomInt << std::endl;
std::cout << randomFloat << std::endl;
    
}
