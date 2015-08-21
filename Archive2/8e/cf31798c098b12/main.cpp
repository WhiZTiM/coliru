#include <iostream>
#include <string>
#include <atomic>
#include <memory>

int foo(void*, uint16_t);
int& foo_ref(void*, uint16_t);

auto make_int_f() { return [](void* base, uint16_t offset){ return *reinterpret_cast<int*>(reinterpret_cast<uint8_t*>(base)+offset); }; }
auto make_intref_f() { return [](void* base, uint16_t offset) -> int& { return *reinterpret_cast<int*>(reinterpret_cast<uint8_t*>(base)+offset); }; }
auto make_int_f_e() { return [](void* base, uint16_t offset) -> int { throw "Error: access to undefined variable"; }; }

struct A 
{
    uint8_t * base_;
    
    //typedef int(*INT_F)(void*, uint16_t);
    typedef decltype(&foo) INT_F;
    typedef int&(*INTREF_F)(void*, uint16_t);
    INT_F a;
    INTREF_F a_ ;

    A() : a(make_int_f()) {}
    void set_func() { a = make_int_f(); }
    void set_func_e() { a = make_int_f_e(); }
    void set_func_ref() { a_ = make_intref_f(); }
};

int main()
{
    char buf[100];
    A a;
    try {
    a.set_func();
    //a.set_func_e();
    a.set_func_ref();
    a.a_(buf, 0) = 4;
    
    std::cout << "a="<<a.a(buf, 0)<<std::endl;
    }
    catch (const char * e) {
        std::cout <<"exception thrown : " << e << std::endl;
    }
}
