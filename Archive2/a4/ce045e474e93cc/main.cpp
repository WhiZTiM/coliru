#include <tuple>

template<typename T>
class synchronized
{   
    struct Locker
    {
        Locker(synchronized* s) : s{s}, lock{s->m} { } 
        T& operator . () { return s->obj; }
    
    private:
        synchronized* s;
        std::unique_lock<std::mutex> lock;
    };
    
public:
    Locker operator . () { return {this}; }

private:
    T obj;
    std::mutex m;
};

struct object
{
    void foo() { }
    void bar() { }
};

int main() 
{
    synchronized<object> obj;
    
    obj.foo();
    obj.bar();
}

