
static int foo( int& i ) { return ++i ; }

static int bar( int& i ) { if( i < 100 ) i = 100 ; else --i ; return i+5 ; }

int foobar()
{
    int v = 23 ; // constant folding: at this point v == 23
    
    --v ; // def-use analysis; can be postponed till v is used
    int temp = v + 56 ; //  def-use analysis; initialisation of temp can be postponed
    v += 10 ; // can combine with the postponed --v to get v += 9 
              // constant folding: at this point v == 32
              
    if( v == 6 ) /* false */ return temp ; // dead code          
              
    temp = v > 75 ? 67 : v ; // v > 75 ? is false; replace with int temp = v
                             // constant folding: replace with int temp = 32
                             // flow analysis: k is never modified later and temp is never aliased: 
                             // replace with constexpr int temp = 22; optimise away temp: substitute 22 for temp
                                 
    if( v < temp ) /* false */ { foo(v) ; /* dead code: eliminate */ }                              
    bar(v) ; // auto inline, v is less than 100, constant folding: at this point v == 100
    
    return v - temp ; // return 100 - 32 ; return 68 ; can also optimise away v 
    
    // generated code
    /*
     _Z6foobarv:                             # @_Z6foobarv
    .cfi_startproc

    movl $68, %eax
	retq 
    */
}
