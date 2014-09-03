
struct Base
{
    virtual ~Base() = default;

    virtual Base *f() const = 0;
};

struct A
: virtual Base
{
    virtual A *f() const override = 0;
};
struct B
: virtual Base
{
    virtual B *f() const override = 0;
};

struct Middle
: virtual A
, virtual B
{
    //Fixes compilation issue, but
    //cannot actually be done in original code
    virtual Middle *f() const override = 0;
};

struct Derived
: Middle
{
    virtual Derived *f() const override = 0;
};

int main()
{
}
