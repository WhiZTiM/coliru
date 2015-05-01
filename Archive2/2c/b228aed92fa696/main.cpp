#include <string>
#include <iostream>
#include <vector>

int main() {
    std::vector<std::pair<std::string, std::string>> records;
    
    std::string column = "hello";
    std::string value = "world";
    
    records.emplace_back(column, value);
    records.emplace_back("new", "value");
    
    for (auto& record : records) {
        std::cout << record.first << ": " << record.second << std::endl;
    }
}