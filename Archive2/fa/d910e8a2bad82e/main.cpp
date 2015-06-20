#include <funkcjonalna> 
#include <iostream>
 
struct Foo { 
    Foo ( int num )  : num_ ( num )  { } 
    void print_add ( int i )  const  {  std :: cout  << num_ + i <<  ' \ n ' ;  } 
    int num_ ; 
} ;
 
void print_num ( int i ) 
{ 
    std :: cout  << i <<  ' \ n ' ; 
}
 
struct PrintNum { 
    void operator ( ) ( int i )  const 
    { 
        std :: cout  << i <<  ' \ n ' ; 
    } 
} ;
 
int main ( ) 
{ 
    // funkcja przechowywania bezpłatną 
    std :: funkcję < void ( int ) > f_display = print_num ; 
    f_display ( - 9 ) ;
 
    // Zapisanie lambda 
    std :: funkcję < void ( ) > f_display_42 =  [ ] ( )  { print_num ( 42 ) ;  } ; 
    f_display_42 ( ) ;
 
    // Zapisanie wyniku połączenia do std :: powiązania 
    std :: funkcję < void ( ) > f_display_31337 =  std :: wiążą ( print_num, 31337 ) ; 
    f_display_31337 ( ) ;
 
    // Przechowywać połączenie z funkcji członka 
    std :: function < void ( const Foo & , int ) > f_add_display =  & Foo :: print_add ; 
    const Foo foo ( 314159 ) ; 
    f_add_display ( foo, 1 ) ;
 
    // Przechowywać wywołanie funkcji składowej i obiekt 
    za pomocą std :: zastępcze :: _1 ; 
    std :: funkcja < void ( int ) > f_add_display2 =  std :: wiążą (  & Foo :: print_add , bla, _1 ) ; 
    f_add_display2 ( 2 ) ;
 
    // Przechowywać wywołanie funkcji składowej i obiektu ptr 
    std :: funkcję < void ( int ) > f_add_display3 =  std :: wiążą (  & Foo :: print_add , & foo, _1 ) ; 
    f_add_display3 ( 3 ) ;
 
    // Przechowywać połączenia na obiekt funkcji 
    std :: funkcję < void ( int ) > f_display_obj = PrintNum ( ) ; 
    f_display_obj ( 18 ) ; 
}