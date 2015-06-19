public:
    void foo(){ const int * p = &a; }
private:
    static const int a = 1;
};

int main ()
{
    A a;
    a.foo();
}