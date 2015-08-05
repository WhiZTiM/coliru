#include <iostream>
#include <random>
#include <iterator>
#include <algorithm>
#include <sstream>

int main() {
    std::random_device r;
    std::seed_seq seed{r(),r(),r(),r(),r(),r(),r(),r()};
    std::mt19937 eng{seed};
    
    std::uniform_int_distribution<char> letter{'A', 'Z'};
    std::uniform_int_distribution<> number{0, 1000};
    
    std::stringstream ss;
        
    std::generate_n(std::ostream_iterator<std::string>(std::cout, "\n"), 100, [&] {
        ss.str("");
        ss << letter(eng) << letter(eng) << "-" << number(eng);
        return ss.str();
    });
}
