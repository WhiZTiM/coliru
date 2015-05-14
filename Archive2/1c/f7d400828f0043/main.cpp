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

typedef struct Block
{

    Block(int blockNum, std::vector<char> const &data, std::vector<char> const &blockHash,
          int blockNonce, int parentBlockId, bool isAdded) : blockNum(blockNum), data(data),
                                                             blockHash(blockHash),
                                                             blockNonce(blockNonce),
                                                             parentBlockId(parentBlockId),
                                                             isAdded(isAdded) { }
    
    Block(const Block &other){
        this->blockNum = other.blockNum;
        this->data = other.data;
        this->blockHash = other.blockHash;
        this->blockNonce = other.blockNonce;
        this->parentBlockId = other.parentBlockId;
        this->isAdded = other.isAdded;
        
    }

    int blockNum;
    std::vector<char> data;
    std::vector<char> blockHash;
    int blockNonce;
    int parentBlockId;
    bool isAdded;
}Block;

int main()
{  
    std::map<int,Block> m;
    const char * data = "abcd";
    std::vector<char> vec(data, data + 4);
    Block b = Block(1,vec,vec,0,0,false);
    m[0] = b;
    std::cout << b.data << b.blockNonce << std::endl;
}
