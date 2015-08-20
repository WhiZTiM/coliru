#include <random>
#include <numeric>
#include <algorithm>
#include <iterator>
#include <iostream>
 
int main()
{
    std::vector<int> v(10) ; 
    std::iota (std::begin(v), std::end(v), 0); 

    std::random_device rd;
    std::mt19937 g(rd());
 
    for(int i=0;i<10;i++){
    std::shuffle(v.begin(), v.end(), g);
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";
    }
}