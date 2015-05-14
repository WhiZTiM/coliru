#include <iostream>
#include <string>
#include <vector>
#include <map>



template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

struct Block
{

    Block(int blockNum, std::vector<char> const &data, std::vector<char> const &blockHash,
          int blockNonce, int parentBlockId, bool isAdded) : blockNum(blockNum), data(data),
                                                             blockHash(blockHash),
                                                             blockNonce(blockNonce),
                                                             parentBlockId(parentBlockId),
                                                             isAdded(isAdded) { }

    int blockNum;
    std::vector<char> data;
    std::vector<char> blockHash;
    int blockNonce;
    int parentBlockId;
    bool isAdded;
};

int main()
{  
    std::map<int,Block> m;
    const char * data = "abcd";
    std::vector<char> vec(data, data + 4);
    Block b(1,vec,vec,0,0,false);
    m.emplace(std::make_pair(1,b));
    std::cout << b.data << b.blockNonce << std::endl;
}
