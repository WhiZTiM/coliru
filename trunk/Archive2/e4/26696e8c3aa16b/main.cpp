// you can use includes, for example:
// #include <algorithm>
#include <iostream>
#include <vector>
// you can use includes, for example:
#include <string>
#include <set>
#include <algorithm>
#include <array>
// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;
long factorial(int N)
{
    long result = 1;
    for (int i = 2; i <=N; i++)
    {
        result *=i;
    }
    return result;
}

int solution(int N) {
    // write your code in C++11
    
    std::string numbers = std::to_string (N);
    //std::cout << numbers <<std::endl;
    std::array<int,10> numbers_map{{0,0,0,0,0,0,0,0,0,0}};
 
    for (auto i : numbers)
    {
        switch (i) 
        { 
            case '0' : ++ numbers_map[0];
                break;
            case '1' : ++ numbers_map[1];
                break;
            case '2' : ++ numbers_map[2];
                break;
            case '3' : ++ numbers_map[3];
                break;
            case '4' : ++ numbers_map[4];
                break;
            case '5' : ++ numbers_map[5];
                break;
            case '6' : ++ numbers_map[6];
                break;
            case '7' : ++ numbers_map[7];
                break;
            case '8' : ++ numbers_map[8];
                break;
            case '9' : ++ numbers_map[9];
        }
    }
    //all permutations
    long num_perm = factorial(numbers.size());
    std::cout << " all permutations " << num_perm << std::endl;
    //duplicate permutations
    long rep_perm = 1;
    for (auto i : numbers_map)
    {
        if (i>1) rep_perm *= factorial(i);
    }
    std::cout << " duplicate permutations " << rep_perm << std::endl;
    num_perm /=rep_perm;
    std::cout << " adjusted for duplicates permutations " << num_perm << std::endl;

    //adjust for zero
    int zeros = numbers_map[0];
    if (zeros > 0 && numbers.size() > 1)
    {
        long zero_perm = factorial(numbers.size() -1);
        std::cout << " zero all permutations " << zero_perm << std::endl;
    
        long zero_dup_perm = rep_perm/zeros;
        std::cout << " zero duplicate permutations " << zero_dup_perm << std::endl;
        zero_perm/=zero_dup_perm;
        std::cout << " zero permutations " << zero_perm << std::endl;
        num_perm -= zero_perm;
    }
    return num_perm;
}
int main()
{
std::cout << solution(1000000000);
} 