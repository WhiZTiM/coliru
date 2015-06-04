#include <iostream>

int main() {
    constexpr const int max_length = 30;
    int line_length = 0;
    std::string buffer;
    while (std::cin >> buffer) {    
        std::cout << (line_length + buffer.size() >= max_length ? (line_length=0, '\n') : (++line_length, " "[line_length==1]));
        std::cout << buffer;
        line_length += buffer.size();
    }
}
