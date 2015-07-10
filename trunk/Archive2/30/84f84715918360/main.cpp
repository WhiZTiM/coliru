#include <cstdio>
#include <new>


struct Foo {
    Foo(int) {puts("Ctor");}
    ~Foo() {puts("Dtor");}
    Foo(const Foo&) {puts("CCtor");}
    Foo& operator= (const Foo&) {puts("AssOp");return *this;}
};


int main() {
    Foo foo(1);
    
    puts("====");
    {
        char memory[4];
        
        void* ptr = memory;
        
        *(reinterpret_cast<Foo*>(ptr)) = foo;
    }
    puts("----");
    {
        char memory[4];
        
        void* ptr = memory;
        
        new (ptr) Foo(foo);
    }
    puts("----");
    
    //for completeness
    {
        char memory[4];
        
        void* ptr = memory;
        
        new (ptr) Foo(1);
    }
    puts("====");
}
