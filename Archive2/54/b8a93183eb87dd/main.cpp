#include <cstdlib> 
#include <iostream> 
#include <ctime>
 
int principal ( )  
{ 
    std :: srand ( std :: vez ( 0 ) ) ;  // utilizar el tiempo actual como semilla para el generador aleatorio 
    int random_variable = std :: rand ( ) ; 
    std :: cout  <<  "valor aleatorio en [ 0 "  <<  RAND_MAX  <<  "]:"  
              << random_variable <<  ' \ n ' ; 
}