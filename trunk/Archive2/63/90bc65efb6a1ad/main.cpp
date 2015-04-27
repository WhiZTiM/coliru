auto __attribute__ ((noinline)) func(int x, int y)
{
    return x + y;
}

int main()
{
    volatile auto x = 1;
    volatile auto y = 2;
    auto volatile r = func(x, y);
}