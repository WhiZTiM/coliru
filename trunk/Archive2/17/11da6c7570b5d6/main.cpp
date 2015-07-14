#include <iostream> 
#include <list> 
#include <iterator> 
#include <algorithm> 
#include <cstring>
using namespace std; 
 
 void doStuff(std::string & str)
 {
     size_t qwe;
     while ( (qwe = str.find(' '))!=std::string::npos)
     {
//        str.replace(qwe, std::string::npos,  str.substr(qwe+1));
//        std::string::iterator it = str.begin() + qwe;
//        std::cout<<qwe;
        str.erase(qwe,1);
     }
     
//     std::for_each(std::string::const_itertator it = str.cbegin(); it != str.end; ++i)
//     {
//         std::swap
//     }
//    std::string::itertator it = str.begin()-1;
//     while(++it != str.end())
//     {
//      std::swap(str.begin(), str.rbegin());   
//     }
//     str.replace(str.begin(), str.rbegin(), str);
//     str.remove(pos);
 }
 
 char * concat (const char * first, const char * second)
 {
     char  * qwe = static_cast<char*>(malloc (sizeof(char) * (strlen(first)+strlen(second)+1)));
     strcat(qwe,first);
     strcat(qwe,".");
     strcat(qwe,second);
     return qwe;
 }
 
 std::string concat(const std::string & first, const std::string & second)
 {
     std::string tmp(first);
     tmp+='.';
     tmp.append(second);
     return tmp;
 }
 
int main() { 
    std::string qwe = "Hello FUCKEN  World\n";
    doStuff(qwe);
   std::cout<<qwe;
   char * tmp = concat("Hi nigger","ololo");
   std::cout<<tmp;
   free(tmp);
//   list<int>::reverse_iterator rpos(pos.end()); 
//   cout<< *(rpos) <<' '; 

//   list<int>::iterator rrpos;  
//   rrpos=rpos.base(); 
//   cout<< *rrpos <<' '; 
   return 0; 
}