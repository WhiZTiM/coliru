
// foo() and bar() are nearly indentical
// yet they result in different code generation
struct Class
{       
    int foo(int local_variable)
    {
        member_variable = local_variable;
        inline_function();
        return member_variable;
    }
    
    int bar(int local_variable)
    {
        member_variable = local_variable;        
        non_inline_function();
        return member_variable;
    }
    
    void inline_function() {}
    
    void non_inline_function(); // Empty body is defined in .cpp file. I promise its body is empty, compiler!
    
    int member_variable;
};



int test_foo_byval(Class c)
{
    return c.foo(123);
}


int test_foo_byref(Class& c) // passing by ref is faster, right?
{
    return c.foo(123);
}


int test_bar_byval(Class c)
{
    return c.bar(123);
}



// test_foo_byval(Class): // arg by-value and inline calls allow the compiler to safely optimize all code
//     mov    eax, 123                          => write value to return register
//     ret


// test_foo_byref(Class&): // arg by-ref prevents some optimizations
//     mov    DWORD PTR [rdi], 123              => write 123 to mysterious memory location (wherever &c resides)
//     mov    eax, 123                          => read 123 from register
//     ret


// test_bar_byval(Class): // non-inline call also prevents optimizations
//     sub    rsp, 24
//     mov    rdi, rsp
//     mov    DWORD PTR [rsp], 123               => write 123 to stack memory
//     call    Class::non_inline_function()      => non-inline function call prevents optimization of above/below reads/writes
//     mov    eax, DWORD PTR [rsp]               => read value from the previously written memory
//     add    rsp, 24
//     ret

