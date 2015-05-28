#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
 
int main()
{
    std::vector<std::string> words = {
        "this", "sentence", "is", "not", "a", "sentence",
    "this", "sentence", "is", "a", "hoax"
    };
 
    std::unordered_map<std::string,size_t>  word_map;
    for (auto w : words) {
        ++word_map[w];
    }
 
    for (auto elem : word_map) {
        std::cout << elem.second
              << " occurrences of word '"
              << elem.first << "'\n";
    }
}