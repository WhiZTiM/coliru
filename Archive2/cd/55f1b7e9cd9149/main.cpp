int MyFunction()
{
    int x = 5;
    return x;
}

void MyOtherFunction( int& val)
{}

int main()
{
     MyOtherFunction(MyFunction());   
}