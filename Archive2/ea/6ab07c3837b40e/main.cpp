class Foo {
    friend void foo();
    
    struct Bar {};
};

void foo() {
    Foo::Bar bar;   
}

int main() {}