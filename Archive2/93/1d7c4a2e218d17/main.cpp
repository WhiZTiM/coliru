#include <iostream>
#include <sstream>

int main()
{
    std::stringstream ss;
    ss << "UPDATE `myTable` SET ";
    
    ss << "`Field1` = \"value\","
       << "`Field2` = \"value\","
       << "`Field3` = \"value\",";
    
    ss.seekp(-1, std::ios_base::cur);
    ss << " WHERE `Field4` = \"value\"";
    
    
    std::cout << ss.str() << '\n';
}