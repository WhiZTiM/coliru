class D {};

class MD {
    D d_d;

  public:
    MD(int i) {}
    int fn() { return 0; }

    const D* operator->() { return &d_d; }
};

void test(MD* val)
{
    {
        MD val(val->fn());
    }
}

int main()
{
    MD md(0);
    test(&md);
}