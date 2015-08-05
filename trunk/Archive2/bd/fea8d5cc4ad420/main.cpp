



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
    
    void non_inline_function(); // empty body is defined in .cpp file (Dear compiler, I promise its body is really empty.)
    
    int member_variable = 0;
    
};


int test_inline_byval(Class c)
{
    return c.foo(123);
}

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
//     mov    DWORD PTR [rsp], 123               => write to stack memory (slower than register, but it's hot in cache)
//     call    Class::non_inline_function()      => non-inline function call prevents optimization of surrounding reads/writes
//     mov    eax, DWORD PTR [rsp]               => read value from memory again
//     add    rsp, 24
//     ret


// test_noninline_byref(Class& c):
//     push    rbx
//     mov    DWORD PTR [rdi], 123              => write to stack/heap memory (wherever &c resides). potential cache miss? (or just a write to the store-buffer?)
//     mov    rbx, rdi
//     call    Class::non_inline_function()     => non-inline function call prevents optimization of surrounding reads/writes
//     mov    eax, DWORD PTR [rbx]              => read value from memory stack/heap(?) again. potential cache miss.
//     pop    rbx
//     ret
