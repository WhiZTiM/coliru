#include <iostream>

int main() {
    constexpr const int max_length = 30;
    int line_length = 0;
    std::string buffer;
    while (std::cin >> buffer) {
        if (line_length + buffer.size() + 1 > max_length) {
            std::cout << "\n";
            line_length = buffer.size();
        } else {
            if (line_length > 0) {
                std::cout << " ";
                line_length++;
            }
            line_length += buffer.size();
        }
        std::cout << buffer;
    }
}