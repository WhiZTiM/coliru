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
    UserType ut1{}, ut2{};
     
    using namespace std;
    using namespace std::chrono;
     
    auto start = steady_clock::now();
    ut2 = std::move(ut1);
    UserType ut3{std::move(ut2)};
    //ut2 = ut1;
    //UserType ut3{ut2};
    auto end = steady_clock::now();
     
    cout << "Time for move ctor + move assignment (micros) = "
    << duration_cast<microseconds>((end-start)).count()
    << endl;
     
    UserType ut4{}, ut5{};
     
    start = steady_clock::now();
    ut5 = ut4;
    UserType ut6{ut5};
    end = steady_clock::now();
     
    cout << "Time for copy ctor + copy assignment (micros) = "
    << duration_cast<microseconds>((end-start)).count()
    << endl;
     
    return 0;
}