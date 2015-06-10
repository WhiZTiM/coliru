void func(int* i)
{
    *i = 44;
}

int main()
{
    int myVal; // gcc will print warning: 'myVar' may be used uninitialized in this function
    func(&myVal);
    //...
}