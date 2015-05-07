struct B {
    virtual void f() = 0;
};

struct D : B { };
 
int main() {
    D d;
}
 
