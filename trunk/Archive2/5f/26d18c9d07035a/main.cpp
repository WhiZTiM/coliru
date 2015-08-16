#include <iostream>

void test(int*& input, int*& output) {
    std::cout << input << "\t" << output << std::endl;
    if(input[0] == 0) {
        output = input;
    }
}

int main()
{
    int *input = new int[3];
    int *output = new int[3];
    std::cout << input << "\t" << output << std::endl;
    
    input[0] = 0;
    
    test(input, output);
    std::cout << input << "\t" << output << std::endl;
}