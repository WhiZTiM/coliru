#include <iostream>
#include <random>

struct MachineRecord
{
    int actualOutput;
    int expectedOutput;
}; 

MachineRecord random_record()
{
    static std::mt19937 rng(std::random_device{}());
    static std::uniform_int_distribution<> dist(1, 30); //Output can be in range [1; 30]
    return MachineRecord{dist(rng), dist(rng)};
}

int main()
{
    constexpr int machines = 4;
    constexpr int months = 12;
    MachineRecord MT[machines][months];
    //Fill array
    for(auto& row: MT) for(auto& m: row)
        m = random_record();

    //Output
    for(auto& row: MT) {
        for(auto& m: row)
            std::cout << m.actualOutput << ':' << m.expectedOutput << ' ';
        std::cout << '\n';
    }
}