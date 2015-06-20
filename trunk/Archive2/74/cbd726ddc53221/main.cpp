 
// T () wygeneruje żadnych wyjątków 
template  < class T > 
  void foo ( )  noexcept ( noexcept ( T ( ) ) )  { }
 
void bar ( )  noexcept ( prawda )  { } 
void baz ( )  noexcept  {  throw  42 ;  }   // noexcept jest taki sam jak noexcept (prawda)
 
int main ( )  
{ 
    foo < int > ( ) ;   // noexcept (noexcept (int ())) => noexcept (prawda), więc to jest w porządku
 
    bar ( ) ;   // porządku 
    baz ( ) ;   // kompiluje, ale w czasie wykonywania wymaga to std :: wypowiedzenia 
}