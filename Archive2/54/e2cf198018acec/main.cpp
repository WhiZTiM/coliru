#include <iostream>
 
Char array1 [ ]  =  "Foo"  "bar" ; 
// o mesmo que 
Char array2 [ ]  =  {  'F' , 'o' , 'o' , 'b' , 'a' , 'r' , ' \ 0 '  } ;
 
const  de char * s1 = R "foo (
Olá
Mundo
) Foo " ; 
// o mesmo que 
const  de char * s2 =  " \ n Olá \ n Mundo \ n " ;
 
int principal ( ) 
{ 
    std :: cout  << array1 <<  ' \ n '  << array2 <<  ' \ n ' ;
 
    std :: cout  << s1 << s2 ; 
}