#include <iostream>
#include <ctime>
#include <random>
#include <chrono>
#include <iomanip>

using namespace std;


int main()
{
    using myclock = std::chrono::high_resolution_clock;
    myclock::time_point beginning = myclock::now();
    
    std::time_t now_c = std::chrono::system_clock::to_time_t(beginning);
    std::tm tm = *std::localtime(&now_c);
    std::cout << std::put_time(&tm, "%H %M %S") << '\n';
    
    auto nowSinceEpoch = std::chrono::high_resolution_clock::now().time_since_epoch();
    cout << nowSinceEpoch.count() << endl;    
        
    std::default_random_engine generator(nowSinceEpoch.count());
    std::uniform_int_distribution<int> distribution(1,6);
    cout << distribution(generator) << endl;	
}
