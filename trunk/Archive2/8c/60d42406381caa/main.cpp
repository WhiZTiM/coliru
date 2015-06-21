struct V {
    V();
    virtual void f() const = 0;
};

struct D1 : public virtual V {
    D1(int, int);
    D1(int);
};

struct D2 : public virtual V {
    D2(int, int);
};

struct C : public D1, public D2
{
    C()
    :
        D1{0, 0}, // <-- curly braces causes error
        // D1{0}, // <-- one argument, no error
        D2(0, 0)  // <-- regular braces, no error
    {}
};

int main()
{
}