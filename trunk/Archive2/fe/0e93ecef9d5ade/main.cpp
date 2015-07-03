#include <string>
#include <algorithm>
#include <iostream>


void reverseString (std::string &src)
{

    int m_size = src.size();
    for (int i = 0, i < m_size; ++i)
    {
        if (src[i] == ' ')
        {
            
        }
    }
    
    
//    for (int i = 0; i < len / 2; ++i)
//    {
//        std::swap(src[i] , src[len-1-i] );
//        tmp = src[i];
//        src[i] = src[len-
//    }
//    std::cout<<src;

}


int main()
{
   // char * someText = new char[4];
    std::string * someText = new std::string("Some Text !");
    reverseString (*someText);
 //   strcpy(someText, "Text");
//    std::cout<<someText<<std::endl;
//    std::cout<<sizeof(someText);
//    reverseString(someText,/*sizeof(someText)*/ 4);
//    std::cout<<someText;
    return 0;
}
