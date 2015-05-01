#include <iostream>
#include <string>
#include <utility>

template <typename T, typename... Args>
std::string tokenize(const std::string str, const size_t start, const Args... args) {
    
    size_t pos = std::string::npos;
    
    auto get_delim_pos = [&, pos](  const std::string str,
                                    const size_t start,
                                    const T c,
                                    const Args... args) {
        while (pos == std::string::npos && sizeof...(args) > 0) {
            pos = str.find(c);
            get_delim_pos(str, start, args...);
        } 
    }();
    
    std::string result;
    
    if(pos != std::string::npos)
        result = str.substr(start, pos);
    
    std::cout << "result: " << result << std::endl;
    
    return result;
}

int main()
{
    std::string buffer;
    
    std::getline(std::cin, buffer);
    
    std::cout << tokenize<char>(buffer, 0, ' ', '\n') << '\n';
    
    return 0;
}
