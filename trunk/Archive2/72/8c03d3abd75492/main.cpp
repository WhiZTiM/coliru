struct foo
{
    const int
        *const a,
        *const b, 
        *const c;

    foo(int a, int b, int c)
            : a(_a), b(_b), c(_c)
            , _a{a}, _b{b}, _c{c}
    {
        *_a = a;
        *_b = b;
        *_c = c;
    }

private:
    int _a[1], _b[1], _c[1];

};

int main()
{}
