namespace
{
    unsigned int at_namespace_scope_with_internal_linkage = 0 ;
}

int foobar()
{
    // def-use analysis: we can postpone this assignment till
    // 'at_namespace_scope_with_internal_linkage' is used
    at_namespace_scope_with_internal_linkage -= 100 ;
    
    /* const */ auto a = 52 ; // constant folding: use 52 for 'a' till 'a' is given a new value
                              // def-use analysis: everywhere ( 'a' is never given a new value )

    auto b = a / 2 ; // constant folding: b = 52/2 ; use 26 for 'b' till 'b' is given a new value
    auto c = a + 5 ; // constant folding: use 57 for 'c' till 'c' is given a new value

    if( b < a ) // constant folding: 26<52 is true generate code as if the if statement did not exist
    {
        b += a ; // b += 52 ; constant folding: use 78 for 'b' till 'b' is given a new value
                 // def-use analysis: postpone assignment to b till 'b' is used 

        c -= a ; // c -= 52 ; constant folding: use 5 for 'c' till 'c' is given a new value
                 // def-use analysis: postpone assignment to 'c' till 'c' is used 
    }

    b *= a ; // def-use analysis: 'b' redefined before it is used
             // generate no code for line 20 and rewrite this as: b = (b+a) * a
             // constant folding: rewrite this as b = 4056

    if( b < c ) // constant folding: 4056<5 is false generate code as if the if statement did not exist
                // dead code elimination: generate no code for the statements inside this if block
    {
        b += a ;
        --c ;
    }

    else // true : ignore the if-else construct and 
         // just generate code for the statements inside the else block
    {
        b -= a ; // def-use analysis: generate no code for line 27
                 // constant folding: rewrite this as b = 4004
                 // def-use analysis: postpone assignment to 'b' till 'b' is used 


        ++c ; // def-use analysis: generate no code for line 23
              // constant folding: rewrite as c = 6
              // def-use analysis: postpone assignment to c till 'c' is used
    }

    // def-use analysis, constant-folding: generate no code for line 10
    // and rewrite as at_namespace_scope_with_internal_linkage -= 48
    // def-use analysis: we can postpone this assignment till
    // 'at_namespace_scope_with_internal_linkage' is used
    at_namespace_scope_with_internal_linkage += a ;

    ++b ; // def-use analysis: generate no code for line 41 and rewrite this as: b = b - a + 1 + 1
          // constant folding: rewrite as b = 4005

    --c ; // def-use analysis: generate no code for line46 and rewrite this as: c = 5

    // def-use analysis, constant-folding: generate no code for line 55
    // and rewrite this as at_namespace_scope_with_internal_linkage = 0 ;
    at_namespace_scope_with_internal_linkage += a - 4 ;
    // dead code elimination: generate no code for line 64

    return a + b + c ; // rewrite this as return 52 + 4005 + 5 ;
                       // "as-if" rule: eliminate objects 'a', 'b', and 'c' altogether
                       // ie. generate code "as-if" the function consisted of just one line: return 4062 ;
                       
    /*
        movl $4062, %eax # imm = 0xFDE
	    retq
    */
}
