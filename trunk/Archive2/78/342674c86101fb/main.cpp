#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <algorithm>

std::random_device rd;
std::mt19937 mt(rd()); //std::chrono::system_clock::now()
std::uniform_real_distribution<double> distribution(1, 10);


struct Point
{
    float x;
    float y;
};

float distance(Point a, Point b)
{
    float x = std::abs(a.x-b.x);
    float y = std::abs(a.y-b.y);
    return std::sqrt(x*x + y*y);
}

template<typename Iterator>
Iterator getElement(Iterator begin, Iterator end)
{
    //int n = hydra::RandomUtils::getInt(0, static_cast<int>(std::distance(begin, end)));
    std::uniform_real_distribution<double> distribution(0, std::distance(begin, end));
    int n = distribution(mt);
    std::advance(begin, n);
    return begin;
}

int main() 
{
    std::vector<int> v = {3,2,5,1};
    std::cout <<  " " << *getElement(v.begin(), v.end());
    std::cout << *std::min_element(v.begin(), v.end()) << std::endl;
}