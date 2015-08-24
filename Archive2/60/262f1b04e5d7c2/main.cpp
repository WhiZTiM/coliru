struct V {
    V();
    virtual void f() const = 0;
};

struct D1 : virtual V {
    D1(int, int);
    D1(int);
};

struct D2 : virtual V {
    D2(int, int);
};

struct C : D1, D2
{
    C()
    :
        //D1{0, 0}, // <-- curly braces causes error
        D1{0}, // <-- one argument, no error
        D2(0, 0)  // <-- regular braces, no error
    {}
};

int main()
{
}