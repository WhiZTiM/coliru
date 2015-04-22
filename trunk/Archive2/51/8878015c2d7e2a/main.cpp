
/*
Author : Prashant
Demo for https://www.linkedin.com/groups/Why-we-need-delete-after-86998.S.5996577458663473154

*/

#include <iostream>

#ifdef FAULTY
class A
{
    A()   {}
   /* A(A&) {}  // Same for Copy Constructor */
    
    static void do_something( void ) ;
};


void A::do_something( void )
{
    A aobj;  // Compiles !!
}

#endif

#ifdef USEDELETE
class B
{
    public:
        B()   = delete ;
       /* B(B& ) = delete ;  // Same for Copy Constructor */
    
    static void do_something( void ) ;
};


void B::do_something( void )
{
    B bobj;  // Doesn't Compile 
}

#endif

#ifdef CPLUSPLUS_03
class C
{
    private:
        C()   ;       /* Having a nice comment helps for future users */
       /* C(C& )  ;  // Same for Copy Constructor */
    
    static void do_something( void ) ;
};


void C::do_something( void )
{
    C cobj;  /* This will issue a linker error, 
                this is nice but we should prefer compile time error over linker errors
             */
}
#endif


int main()
{
    std::cout << "Executed\n\n";
}

