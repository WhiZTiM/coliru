struct foo {
    union {
        int bar;
        double woo;
    };
};

int main()
{
    foo f = { .woo = 2.3 };
}