#include <cstdio> 
#include <límites> 
#include <cstdint> 
#include <cinttypes>
 
int principal ( ) 
{ 
    std :: printf ( "Cuerdas: \ n " ) ;
 
    const  char * s =  "Hola" ; 
    std :: printf ( " \ t ..% 10s \ n \ t ..% - 10s \ n \ t .%. * s \ n " , S, S, 10 , s ) ;
 
    std :: printf ( "Personajes: \ t % c %% \ n " , 65 ) ;
 
    std :: printf ( "Enteros \ n " ) ; 
    std :: printf ( "Decimal: \ t % i% d% .6i% i% .0i% + i% u \ n " , 1 , 2 , 3 , 0 , 0 , 4 , - 1 ) ; 
    std :: printf ( "Hexadecimal: \ t % x% x% X% # x \ n " , 5 , 10 , 10 , 6 ) ; 
    std :: printf ( "Octal: \ t % o% # o% # o \ n " , 10 , 10 , 4 ) ;
 
    std :: printf ( "punto flotante \ n " ) ; 
    std :: printf ( "Redondeo: \ t % f% .0f% .32f \ n " , 1.5 , 1.5 , 1.3 ) ; 
    std :: printf ( "Relleno: \ t % 05.2f% .2f% 5.2f \ n " , 1.5 , 1.5 , 1.5 ) ; 
    std :: printf ( "científico: \ t % E% e \ n " , 1.5 , 1.5 ) ; 
    std :: printf ( "Hexadecimal: \ t % a% A \ n " , 1.5 , 1.5 ) ; 
    std :: printf ( "valores especiales: \ t 0/0 = 1% g / 0 =% g \ n " , 0 . / 0 , 1 . / 0 ) ;
 
    std :: printf ( "Variable de control de ancho: \ n " ) ; 
    std :: printf ( "justificado a la derecha de ancho variable: '% * c' \ n " , 5 , 'x' ) ; 
    int r = std :: printf ( "justificado a la izquierda de anchura variable: '% * c' \ n " , - 5 , 'x' ) ; 
    std :: printf ( "(los últimos% d caracteres impresos printf) \ n " , r ) ;
 
    // tipos de ancho fijo 
    std :: uint32_t val =  std :: numeric_limits < std :: uint32_t > :: max ( ) ; 
    std :: printf ( "Mayor valor de 32 bits es%"  PRIu32  "o% #"  PRIx32  " \ n " , val, val ) ; 
}