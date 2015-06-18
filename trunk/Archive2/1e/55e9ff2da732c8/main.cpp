#include <iostream>
#include <chrono>
#include <vector>
 
struct UserType 
{
    // 10 million ints with value 10
    UserType() : vints(10000000, 100)  {}

    std::vector<int> vints;
};
 
int main() 
{
    UserType ut1{};
    std::vector<UserType> v;
     
    using namespace std;
    using namespace std::chrono;
     
    auto start = steady_clock::now();
    v.push_back(std::move(ut1));
    auto end = steady_clock::now();
     
    cout << "Time for move push_back (micros) = "
    << duration_cast<microseconds>((end-start)).count()
    << endl;
     
    UserType ut4{};
     
    start = steady_clock::now();
    v.push_back(ut4);
    end = steady_clock::now();
     
    cout << "Time for copy push_back (micros) = "
    << duration_cast<microseconds>((end-start)).count()
    << endl;
     
    return 0;
}