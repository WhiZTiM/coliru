class S {
    friend void foo();
    
    struct Inner {};
};

void foo() {
    S::Inner obj;   
}