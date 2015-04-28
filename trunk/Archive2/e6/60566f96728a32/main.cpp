#include <iostream>
#include <map>
#include <string>
#include <boost/crc.hpp> 

struct sStruct {
    int iValue;
    float fValue1;
    float fValue2;
};

int main()
{  
//    std::map<std::string, unsigned int> example = {{"a", 1},{"b", 2}};    
    sStruct my_struct = { 42, 52.5, 5.2};
    
    boost::crc_32_type CRCresult;
    CRCresult.process_bytes((unsigned char*)(&my_struct), sizeof(my_struct));
    unsigned int uiResult = CRCresult.checksum();
    std::cout << std::hex << uiResult << " - ";
    
    std::map<unsigned int, unsigned int> example = {{uiResult, 42},{99, 2}};    
    
    
    auto search = example.find(uiResult);
    if(search != example.end()) {
        std::cout << "Found " << search->first << " " << search->second << '\n';
    }
    else {
        std::cout << "Not found\n";
    }
    
    std::string my_string = "buckeroo";
    
//    boost::crc_32_type result;
    boost::crc_optimal<32, 0x1EDC6F41> result32; 
    boost::crc_optimal<64, 0x42F0E1EBA9EA3693> result; 
    result.process_bytes(my_string.data(), my_string.length());
    result32.process_bytes(my_string.data(), my_string.length());
    std::cout << std::hex << result.checksum() << " " << std::hex << result32.checksum();
    
}