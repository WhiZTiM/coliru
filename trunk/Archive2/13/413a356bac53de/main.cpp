#include <string>


template<typename T>
struct Identity { using type = T; };


template<typename Type>
struct Foo
{
    Type get()
    {
        // pass 0 as second parameter
        return do_get(Identity<Type>(), 0);
    }    
    
private:
    // conversion from int to long required.
    // this reduces the "score" of this function during the overload resolution process    
    Type do_get(Identity<Type>, long) { return Type(); }    
    
    // no conversion required
    // so this overload will be preferred in case Type = void.
    void do_get(Identity<void>, int ) { }
};


int main()
{
    Foo<int> foo_int;
    int n = foo_int.get();
    
    Foo<void> foo_void;
    foo_void.get(); // returns void
}
