#include <iostr//*[@id="js_16"]eam> 
#include <cstring//*[@id="js_a"]>
 
int chính ( ) 
{ 
    char str [ ]  =  "1234567890" ; 
    std :: cout  << str <<  ' \ n ' ; 
    std :: memmove ( str + 4 , str + 3 , 3 ) ;  // sao chép từ [4 , 5,6] để [5,6,7] 
    std :: cout  << str <<  ' \ n ' ; 
}