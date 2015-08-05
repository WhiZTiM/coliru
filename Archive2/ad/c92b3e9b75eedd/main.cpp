
// foo() and bar() are nearly indentical
// yet, they result in different code generation
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
    
    void non_inline_function(); // Empty body is defined in .cpp file. I promise, compiler.
    
    int member_variable;
};



int test_inline_byval(Class c)
{
    return c.foo(123);
}

// passing by ref is faster, right?
int test_inline_byref(Class& c)
{
    return c.foo(123);
}


int test_noninline_byval(Class c)
{
    return c.bar(123);
}


int test_noninline_byref(Class& c)
{
    return c.bar(123);
}



// test_inline_byval(Class):
//     mov    eax, 123                          => write value to return register (fast)
//     ret


// test_inline_byref(Class&):
//     mov    DWORD PTR [rdi], 123              => write 123 to heap/stack memory (wherever &c resides)
//     mov    eax, 123                          => read 123 from register
//     ret


// test_noninline_byval(Class):
//     sub    rsp, 24
//     mov    rdi, rsp
//     mov    DWORD PTR [rsp], 123               => write to stack memory (*much* slower than register access)
//     call    Class::non_inline_function()      => non-inline function call prevents optimization of surrounding reads/writes
//     mov    eax, DWORD PTR [rsp]               => read value from memory again
//     add    rsp, 24
//     ret


// test_noninline_byref(Class& c):
//     push    rbx
//     mov    DWORD PTR [rdi], 123              => write to mysterious memory location (wherever &c resides). potential cache miss? maybe just a store-buffer write?
//     mov    rbx, rdi
//     call    Class::non_inline_function()     => non-inline function call prevents optimization of surrounding reads/writes
//     mov    eax, DWORD PTR [rbx]              => read value from the same mysterious memory location. potential cache miss here? or just a read from the store-buffer?
//     pop    rbx
//     ret
