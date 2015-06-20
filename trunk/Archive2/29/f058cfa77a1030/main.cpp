#include <random> 
#include <iostream> 
#include <Pamięć> 
#include <funkcjonalna>
 
void f ( int n1, int n2, int n3, const  int & N4, int n5 ) 
{ 
    std :: cout  << n1 <<  ''  << n2 <<  ''  << n3 <<  ''  << n4 < <  ''  << N5 <<  ' \ n ' ; 
}
 
int g ( int n1 ) 
{ 
    return n1 ; 
}
 
struct Foo { 
    void print_sum ( int n1, int n2 ) 
    { 
        std :: cout  << n1 + n2 <<  ' \ n ' ; 
    } 
    int danych =  10 ; 
} ;
 
int główne ( ) 
{ 
    przy użyciu  przestrzeni nazw  std :: zastępcze ;   // dla _1, _2, _3 ...
 
    // Pokazuje zmianę kolejności argumentów i przekazywany przez odwołanie 
    int n =  7 ; 
    // (_1 i _2 są z std :: zastępcze, i stanowią przyszłe 
    // argumenty, które będą przekazane do F1) 
    auto f1 = std :: wiążą ( F, _2, _1, 42 , std :: cref ( n ) , n ) , 
    n =  10 ; 
    f1 ( 1 , 2 , 1001 ) ;  // 1 jest związany _2, 2 jest związany _1, 1001 jest używany
 
    // zagnieżdżone podwyrażeń wiążą dzielić zastępcze 
    auto f2 = std :: wiążą ( f, _3, std :: wiążą ( g, _3 ) , _3, 4 , 5 ) , 
    f2 ( 10 , 11 , 12 ) ;
 
    // Częsty przypadek użycia: wiązania RNG z 
    e ) ; // copy of E jest przechowywany w rnd do ( int n = 0 , n < 10 ; ++ n ) std :: Cout << rnd ( ) << '' ; :: std Cout << ' \ n " ;
    
     
     
           
      
 
    // Powiązanie z funkcji członka 
    foo Foo ; 
    auto f3 = std :: wiążą ( & Foo :: print_sum , i bla, 95 , _1 ) , 
    F3 ( 5 ) ;
 
    // Wiążą się z danych członkiem 
    auto f4 = std :: wiążą ( & Foo :: danych , _1 ) ; 
    std :: cout  << f4 ( foo )  <<  " \ n " ;
 
    // inteligentne wskaźniki mogą być używane zadzwonić członków przywoływanych obiektów, zbyt 
    std :: cout  << f4 ( std :: make_shared < Foo > ( foo ) )  <<  " \ n " 
              << f4 ( std :: unique_ptr < Foo > ( new Foo ( foo ) ) )  <<  ' \ n ' ; }