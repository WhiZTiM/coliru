#include <iostream>
#include <chrono>
#include <vector>
 
struct SpawnParams 
{
    // 10 million ints with value 10
    SpawnParams() : myint(100), mydouble(2.f)  {}

    int myint;
    double mydouble;
};
 
int main() 
{
    SpawnParams params1{};
    std::vector<SpawnParams> v;
     
    using namespace std;
    using namespace std::chrono;
     
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