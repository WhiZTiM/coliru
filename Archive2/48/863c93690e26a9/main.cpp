#include <iostream>
#include <map>
#include <string>

union dirty {
    std::int32_t input;
    char output[5] = { '\0' };
};

const std::string hack(std::int32_t input) {
    dirty fun;
    fun.input = input;
    return fun.output;
}

int main() {
    std::map<std::string, int> tester;
    for(int n = 1 ; n < 50 ; ++n) {
        tester[hack(n)] = n;
    }
    for(auto const& iter : tester) {
        std::cout << iter.second << std::endl;
    }
}
