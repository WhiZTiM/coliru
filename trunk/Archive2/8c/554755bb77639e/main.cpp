#include <iostream>
#include <cstdio>

using namespace std ;

typedef void (* fun_t)(void) ;



void fun0(void)
{
    cout << "fun0 called " << endl ;
}

void fun1 ( void )
{
    cout << "fun1 called " << endl ;
}

void fun2 ( void )
{
    cout << "fun2 called " << endl ;
}

 
void (*cb_fun_list[3])(void) = {fun0 ,fun1 , fun2} ;
    
 

void call_back ( int i )
{ 
    fun_t funPtr ;
    
    if (i < 0 || i > 2 )
    {
        cout << " illegal function number " << endl ;
        return ;
    }
    funPtr = cb_fun_list[i] ;
    
    funPtr () ;
    
}


int main ()
{
    
    call_back ( 2 ) ;
    call_back ( 0 ) ;
    call_back ( 1 ) ;
    
    return 0 ;
}