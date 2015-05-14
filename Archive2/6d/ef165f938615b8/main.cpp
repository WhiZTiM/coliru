int* max1()
{
    int a=0;
    int b=0;

    return &a;
}

int* max2()
{
    int a=0;
    int b=0;

    return a > b ? &a : &b;
}

int main(){}