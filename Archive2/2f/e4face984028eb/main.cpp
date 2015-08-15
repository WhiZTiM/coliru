int foo()
{
    return 5;
}

void bar(int&& ref)
{
    ref = 4;
}

int main()
{
    bar(foo());
}