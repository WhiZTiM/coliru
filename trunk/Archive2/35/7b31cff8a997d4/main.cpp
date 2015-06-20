#include <algorytm> 
#include <funkcjonalna> 
#include <iostream> 
#include <vector>
 
struct less_than_7 : std :: unary_function < int , bool > 
{ 
    bool operator ( ) ( int i )  const  {  return i <  7 ;  } 
} ;
 
int main ( ) 
{ 
    std :: vector < int > v ; 
    w  ( int i =  0 ; i <  10 ;  ++ Í ) . v push_back ( Í ) ;
 
    std :: cout  <<  std :: count_if ( v. zacząć ( ) , v. end ( ) , std :: nie1 ( less_than_7 ( ) ) ) ;
 
    / * C ++ 11 Rozwiązanie:
        // Std :: Odlewanie do funkcji <bool (int)> jakiś sposób - nawet z lambda
        std :: cout << std :: count_if (v.begin (), V.END (),
            std :: nie1 (std :: funkcja <bool (int)> ([] (int i) {return i <7;}))
        );
    * / 
}