#include <iostream>
#include <string>
#include <vector>
#include <functional>

struct Data {
    int i;
    Data() : i(0) { std::cout << "Data();" << std::endl; }
    Data(const Data& data){ std::cout << "Data();" << std::endl; i = data.i; }
    ~Data() { std::cout << "~Data();" << std::endl; }
    Data(Data&& data) noexcept { std::cout << "Data(Data&& data);" << std::endl; i = data.i; }
    Data& operator=(const Data& data){ std::cout << "operator=(const Data& data)" << std::endl; i = data.i; return *this; }
    Data& operator=(Data&& data){ std::cout << "operator=(Data&& data)" << std::endl;  i = data.i; return *this; }
};

int main() 
{
    std::vector<Data> srcData(5);
    std::vector<std::vector<Data>> tableData;
    size_t rows = 2;
    size_t cols = 3;
    
    std::cout << "--------- start:" << std::endl;
    size_t i = 0;
    for (size_t x = 0; x < rows && i < srcData.size(); ++x)
    {
        tableData.push_back({});
        for (size_t y = 0; y < cols && i < srcData.size(); ++y)
        {
            tableData.at(x).push_back(srcData.at(i));
        }
    }
    std::cout << "--------- end:" << std::endl;
}