#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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
        std::cout<<*it;;
    }
}

int main()
{

    std::vector<std::string> myVector;
    std::string tmp;
    tmp = "qwe";
    //std::cin>>tmp;
    myVector.push_back(tmp);
    tmp = "asd";
    //std::cin>>tmp;
    myVector.push_back(tmp);
    printVector(myVector);
}
