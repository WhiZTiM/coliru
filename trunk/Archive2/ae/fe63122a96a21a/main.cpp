#include <iostream> 
#include <iomanip> 
#include <ctime>
 
int principal ( ) 
{ 
    std :: time_t t =  std :: tiempo ( NULL ) ; 
    std :: cout  <<  "UTC:"  <<  std :: put_time ( std :: gmtime ( y t ) , "% c% Z " )  <<  ' \ n ' ; 
    std :: cout  <<  "local:"  <<  std :: put_time ( std :: localtime ( y t ) , "% c% Z" )  <<  " \ n " ; 
}