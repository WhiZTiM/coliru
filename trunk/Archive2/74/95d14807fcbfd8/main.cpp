#include <string> 
#include <iterator> 
#include <iostream> 
#include <algorithm> 
#include <array>
 
int principal ( ) 
{ 
    // construção usa agregado inicialização 
    std :: matriz < int , 3 > a1 {  { 1 , 2 , 3 }  } ;  // double-chaves necessária em C ++ 11 (e não em C ++ 14) 
    std :: matriz < int , 3 > a2 =  { 1 , 2 , 3 } ;   // nunca exigiu depois = 
    std :: matriz < std :: seqüência , 2 > a3 =  {  std :: seqüência ( "a" ) , "b"  } ;
 
    // operações de contêineres são suportados 
    std :: tipo ( a1. começar ( ) , a1. end ( ) ) ; 
    std :: reverse_copy ( . a2 começar ( ) ., a2 final ( ) , 
                       std :: ostream_iterator < int > ( std :: cout , "" ) ) ;
 
    std :: cout  <<  " \ n " ;
 
    // Variou loop é suportado 
    para ( const  auto & s : a3 ) 
        std :: cout  << s <<  '' ; 
}