#include <iostream>
#include <stack>
#include <string>
#include <vector>

int main() {
    int count; // how many numbers are there
    std::cin >> count;
    std::string buffer;
    
    //two vectors to store output
    std::vector<long int> input;
    std::vector<long int> output;
    
    //take the inputs
    for(int i = 0; i < count; ++i) {
        std::cin >> buffer;
        input.push_back(std::stoi(buffer));
        buffer.clear();
    }
    
    //check that we have the inputs
    for(auto it : input) {
        std::cout << it << std::endl;
    }
    
    //lambda to test for palindromes
    auto is_palindrome = [](long int n) {
        auto str = std::to_string(n);
        std::stack<char> stack;
        
        //Load each character into the stack
        for(auto it : str) {
           stack.push(it);
        }
        
        for(size_t i = 0; !stack.empty(); stack.pop()) {

            if (stack.top() != str[i])
                return false;
                
            ++i;
        }
        
        return true;
    };   
    
    //test for the palindromes; iterate
    for(auto it : input) {
        int n;
        for (n = it+1; ; ++n) {
            if(is_palindrome(n))
                break;
            else
                continue;
        }
        output.push_back(n);
    }
    
    //output the outputs
    for(auto it : output) {
        std::cout << "next palindrome: " << it << '\n';   
    }
    return 0;
}
