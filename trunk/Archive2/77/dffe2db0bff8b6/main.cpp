#include <iostream>
#include <array>
#include <algorithm>
#include <iterator>
#include <iomanip>
#include <bitset>
#include <climits>

struct No { int decimal; };

int main()
{
    std::size_t size = 10;
    std::vector<int> vector;
    std::generate_n(back_inserter(vector), size, []() { return rand(); });
    
    for (auto const& i : vector)
        std::cout << i << "\t"
                  << std::bitset<CHAR_BIT * sizeof(int)>(i) << "\t\t\t"
                  << std::oct << i << "\t\t"
                  << std::hex << i << "\n"
                  << std::dec;
}