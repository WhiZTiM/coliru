#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

//template<typename T>
//std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
//{
//    for (auto& el : vec)
//    {
//        os << el << ' ';
//    }
//    return os;
//}


void printVector(const std::vector<std::string> & vec)
{
    std::vector<std::string>::const_iterator it;
    for( it = vec.cbegin(); it != vec.cend(); ++it)
    {
        std::cout<<*it<<std::endl;
    }
    std::cout<<std::endl;
}

int main()
{

    std::vector<std::string> myVector;
    myVector.push_back("apple");
    myVector.push_back("pinApple");
    myVector.push_back("arbuz");
    myVector.push_back("cactus");
    myVector.push_back("avakado");
    printVector(myVector);
    std::vector<std::string> tmpVec;
    tmpVec = myVector;  
    std::sort(tmpVec.begin(), tmpVec.end());
    std::vector<std::string>::iterator start = find_if(tmpVec.begin(), tmpVec.end(), [] 
        (const std::string & tmp)
        {
            return tmp[0]=='a' ? true : false;
        }   
        );
    std::vector<std::string>::iterator end = find_if(start, tmpVec.end(), [] 
        (const std::string & tmp)
        {
            return tmp[0]!='a' ? true : false;
        }   
        );   

    tmpVec.erase(start, end);
//    tmpVec.clear();
    std::cout<<"Edited vector:"<<std::endl;
    printVector(tmpVec);
    return 0;
    
}
    