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
    std::map<std::string, int> ts_tester;
    std::map<std::string, int> hack_tester;
    std::cout << "Broken to_string method:" << std::endl;
    for(int n = 1 ; n < 50 ; ++n) {
        ts_tester[std::to_string(n)] = n;
    }
    for(auto const& iter : ts_tester) {
        std::cout << iter.second << std::endl;
    }
    std::cout << "Working hack method:" << std::endl;
    for(int n = 1 ; n < 50 ; ++n) {
        hack_tester[hack(n)] = n;
    }
    for(auto const& iter : hack_tester) {
        std::cout << iter.second << std::endl;
    }
}
