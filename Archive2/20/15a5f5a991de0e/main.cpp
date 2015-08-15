int foo()
{
    return 5;
}

int main()
{
    int&& ref = foo();
    ref = 4;
}