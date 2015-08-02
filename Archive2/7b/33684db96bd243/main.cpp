#include <iostream>
#include <string>
#include <vector>

unsigned int aSolution(unsigned int aim, std::vector<unsigned int>::const_iterator blocksStart, std::vector<unsigned int>::const_iterator blocksEnd){
    if(aim == 0){
        return 0;
    }
    
    auto last = std::next(blocksEnd, - 1);
    auto biggestBlock = *last;
    while(biggestBlock > aim){
        last = std::next(last, - 1);
        biggestBlock = *last;
    }
    
    if(biggestBlock == 1){
        return aim;
    }
    
    auto maxNBiggestBlock = aim/biggestBlock;
    
    return maxNBiggestBlock + aSolution(aim - maxNBiggestBlock*biggestBlock, blocksStart, last);
}

unsigned int solve(unsigned int aim, std::vector<unsigned int>::const_iterator blocksStart, std::vector<unsigned int>::const_iterator blocksEnd, unsigned int max = 0){
    if(max == 0){
        max = aSolution(aim, blocksStart, blocksEnd);
    }
#if 0   
    std::cout << "solve(" << aim << ", {";
    for(auto it = blocksStart; it != blocksEnd; ++it){
        std::cout << *it << ", ";   
    }
    std::cout << "}, " << max << ")" << std::endl;;
#endif    
    if(aim == 0){
        return 0;
    }
    
    auto last = std::next(blocksEnd, - 1);
    auto biggestBlock = *last;
    while(biggestBlock > aim){
        last = std::next(last, - 1);
        biggestBlock = *last;
    }
    
    if(biggestBlock == 1){
        return aim;
    }
    
    auto maxNBiggestBlock = aim/biggestBlock;
    for(auto i = maxNBiggestBlock; i >= 0; --i){
        if(i > max){
            break;
        }
        auto candidate = i + solve(aim - i*biggestBlock, blocksStart, last, max-i);
        if(candidate < max){
            max = candidate;
        }
    }

    return max;
}

int main()
{
    {
        std::vector<unsigned int> blocks = {1, 5, 7, 19, 21, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53};
        std::cout << solve(86, std::begin(blocks), std::end(blocks)) << std::endl;
    }
    
    
    {
        std::vector<unsigned int> blocks = {1, 5, 10, 15, 25, 50};
        std::cout << solve(100, std::begin(blocks), std::end(blocks)) << std::endl;
    }
    
    
    {
        std::vector<unsigned int> blocks = {1, 5};
        std::cout << solve(103, std::begin(blocks), std::end(blocks)) << std::endl;
    }
}

