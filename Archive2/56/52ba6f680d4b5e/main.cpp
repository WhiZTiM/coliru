#include <iostream>
#include <chrono>
#include <vector>
 
struct SpawnParams 
{
    SpawnParams() : myint(100), mydouble(2.f)  {}

    int myint;
    double mydouble;
};
 
int main() 
{     
    using namespace std;
    using namespace std::chrono;
     
    SpawnParams params1{};
    std::vector<SpawnParams> v;
    
    auto start = steady_clock::now();
    v.push_back(std::move(params1));
    auto end = steady_clock::now();
     
    cout << "Time for move push_back (micros) = "
    << duration_cast<microseconds>((end-start)).count()
    << endl;
     
    SpawnParams params2{};
     
    start = steady_clock::now();
    v.push_back(params2);
    end = steady_clock::now();
     
    cout << "Time for copy push_back (micros) = "
    << duration_cast<microseconds>((end-start)).count()
    << endl;
     
    return 0;
}